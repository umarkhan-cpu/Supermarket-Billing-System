#include "Transaction.h"
#include <iostream>

using namespace std;

// constructor
Transaction::Transaction() {
    TransactionID = 0;
    date = "Unknown";
    CashierID = 0;
    TotalAmount = 0.0;
    status = "Unknown";
}

// set data
void Transaction::setData(int TID, string D, int CID, float amount, string st) {
    TransactionID = TID;
    date = D;
    CashierID = CID;
    TotalAmount = amount;
    status = st;
}

// getters
int Transaction::getID() const {
    return TransactionID;
}

string Transaction::getDate() const {
    return date;
}

int Transaction::getCashierID() const {
    return CashierID;
}

float Transaction::getTotalAmount() const {
    return TotalAmount;
}

string Transaction::getStatus() const {
    return status;
}

// display
void Transaction::show() const {
    cout << "Transaction ID: " << TransactionID << "\n"
        << "Date: " << date << "\n"
        << "Cashier ID: " << CashierID << "\n"
        << "Total Amount: " << TotalAmount << "\n"
        << "Status: " << status << "\n"
        << "---------------------------\n";
}

// save file
void Transaction::save(ofstream& out) {
    out << TransactionID << " "
        << date << " "
        << CashierID << " "
        << TotalAmount << " "
        << status << endl;
}

// load file
void Transaction::load(ifstream& in) {
    in >> TransactionID
        >> date
        >> CashierID
        >> TotalAmount
        >> status;
}