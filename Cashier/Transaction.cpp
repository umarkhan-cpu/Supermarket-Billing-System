#include "Transaction.h"
#include <iostream>
#include <sstream>

using namespace std;

// Constructor 
Transaction::Transaction() {
    TransactionID = 0;
    date = "";
    CashierID = 0;
    TotalAmount = 0.0;
    status = "";
}

// Set all values at once
void Transaction::setData(int TID, string D, int CID, float amount, string st) {
    TransactionID = TID;
    date = D;
    CashierID = CID;
    TotalAmount = amount;
    status = st;
}

// Allow updating status 
void Transaction::setStatus(const string& st) {
    status = st;
}

// Getters
int Transaction::getID() const { return TransactionID; }
string Transaction::getDate() const { return date; }
int Transaction::getCashierID() const { return CashierID; }
float Transaction::getTotalAmount() const { return TotalAmount; }
string Transaction::getStatus() const { return status; }

// Display transaction
void Transaction::show() const {
    cout << "ID: " << TransactionID
        << " | Date: " << date
        << " | Cashier: " << CashierID
        << " | Total: " << TotalAmount
        << " | Status: " << status << "\n";
}

// Save
void Transaction::save(ofstream& out) {
    out << TransactionID << ","
        << date << ","
        << CashierID << ","
        << TotalAmount << ","
        << status << "\n";
}

// Original Work by Farda
//// Load
//bool Transaction::load(ifstream& in) {
//    string line;
//    if (!getline(in, line)) return false;
//
//    stringstream ss(line);
//    string id, d, cid, amt, st;
//
//    getline(ss, id, ',');
//    getline(ss, d, ',');
//    getline(ss, cid, ',');
//    getline(ss, amt, ',');
//    getline(ss, st);
//
//    TransactionID = stoi(id);
//    date = d;
//    CashierID = stoi(cid);
//    TotalAmount = stof(amt);
//    status = st;
//
//    return true;
//}

// Modification by Umar (lead): To handle crashes in case of empty transactions.txt file (using try-catch) 
// Load 
bool Transaction::load(ifstream& in) {
    string line;

    // Skip blank lines (e.g. trailing newlines in the file)
    do {
        if (!getline(in, line)) return false;
    } while (line.empty());

    stringstream ss(line);
    string id, d, cid, amt, st;

    getline(ss, id, ',');
    getline(ss, d, ',');
    getline(ss, cid, ',');
    getline(ss, amt, ',');
    getline(ss, st);

    // Defensive parse - if the line is malformed, skip rather than crash
    if (id.empty() || cid.empty() || amt.empty()) return false;

    try {
        TransactionID = stoi(id);
        CashierID = stoi(cid);
        TotalAmount = stof(amt);
    }
    catch (const std::exception&) {
        return false;
    }

    date = d;
    status = st;

    return true;
}