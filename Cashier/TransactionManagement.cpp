#include "TransactionManagement.h"
#include <iostream>
#include <fstream>

using namespace std;

Transaction* TransactionManagement::transactions = nullptr;
int TransactionManagement::count = 0;
int TransactionManagement::capacity = 2;

// Resize array when full
void TransactionManagement::resize() {
    capacity *= 2;

    Transaction* temp = new Transaction[capacity];

    for (int i = 0; i < count; i++)
        temp[i] = transactions[i];

    delete[] transactions;
    transactions = temp;
}

// Add transaction
void TransactionManagement::addTransaction(const Transaction& t) {
    if (transactions == nullptr)
        transactions = new Transaction[capacity];

    if (count == capacity)
        resize();

    transactions[count++] = t;
}

// Show all transactions
/*void TransactionManagement::viewHistory() {
    cout << "\n--- TRANSACTION HISTORY ---\n";

    for (int i = 0; i < count; i++)
        transactions[i].show();
}
*/

// Search by ID
Transaction TransactionManagement::searchByID(int id) {
    for (int i = 0; i < count; i++) {
        if (transactions[i].getID() == id)
            return transactions[i];
    }
    return Transaction();
}

// Search by date
/*void TransactionManagement::searchByDate(const string& date) {
    cout << "\n--- SEARCH RESULTS ---\n";

    for (int i = 0; i < count; i++) {
        if (transactions[i].getDate() == date)
            transactions[i].show();
    }
}
*/

// Refund support (marks transaction as refunded)
bool TransactionManagement::markAsRefunded(int id) {
    for (int i = 0; i < count; i++) {
        if (transactions[i].getID() == id) {
            transactions[i].setStatus("Refunded");
            saveToFile();
            return true;
        }
    }
    return false;
}

// For SalesReport
int TransactionManagement::getCount() {
    return count;
}

Transaction TransactionManagement::getByIndex(int i) {
    if (i < 0 || i >= count)
        return Transaction();
    return transactions[i];
}

// Save to Data folder (IMPORTANT FIX)
void TransactionManagement::saveToFile() {
    ofstream out(R"(C:\Users\mahno\OneDrive\Documents\GitHub\Supermarket-Billing-System\Data\transactions.txt)");

    for (int i = 0; i < count; i++)
        transactions[i].save(out);

    out.close();
}

// Load from Data folder
void TransactionManagement::loadFromFile() {
    ifstream in(R"(C:\Users\mahno\OneDrive\Documents\GitHub\Supermarket-Billing-System\Data\transactions.txt)");

    if (!in) return;

    Transaction t;

    while (t.load(in))
        addTransaction(t);

    in.close();
}

// Cleanup memory
void TransactionManagement::cleanup() {
    delete[] transactions;
    transactions = nullptr;
    count = 0;
    capacity = 2;
}