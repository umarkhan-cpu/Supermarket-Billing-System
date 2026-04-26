#include "TransactionManagement.h"
#include <iostream>
#include <fstream>

using namespace std;

//  initialize static variable 
Transaction* TransactionManagement::transactions = nullptr;
int TransactionManagement::count = 0;
int TransactionManagement::capacity = 2;

// resize array when full
void TransactionManagement::resize() {
    capacity *= 2;

    Transaction* temp = new Transaction[capacity];

    for (int i = 0; i < count; i++) {
        temp[i] = transactions[i];
    }

    delete[] transactions;
    transactions = temp;
}

// add transaction
void TransactionManagement::addTransaction(const Transaction& t) {

    // initialize array if first time
    if (transactions == nullptr) {
        transactions = new Transaction[capacity];
    }

    // resize if full
    if (count == capacity) {
        resize();
    }

    transactions[count] = t;
    count++;
}

// view all transactions
void TransactionManagement::viewHistory() {

    cout << "\n--- TRANSACTION HISTORY ---\n";

    for (int i = 0; i < count; i++) {
        transactions[i].show();
    }
}

// search by ID
Transaction TransactionManagement::searchByID(int id) {

    for (int i = 0; i < count; i++) {
        if (transactions[i].getID() == id) {
            return transactions[i];
        }
    }

    return Transaction(); // empty object if not found
}

// search by date
void TransactionManagement::searchByDate(const string& date) {

    cout << "\n--- SEARCH RESULTS ---\n";

    for (int i = 0; i < count; i++) {
        if (transactions[i].getDate() == date) {
            transactions[i].show();
        }
    }
}

// save  to file
void TransactionManagement::saveToFile() {

    ofstream out("transactions.txt");

    for (int i = 0; i < count; i++) {
        transactions[i].save(out);
    }

    out.close();
}

// load  from file
void TransactionManagement::loadFromFile() {
    ifstream in("transactions.txt");

    if (!in) return;

    Transaction t;

    while (true) {

        t.load(in);

        if (!in) 
            break;   // stop if file ends or read fails
        
        addTransaction(t);
    }

    in.close();
}