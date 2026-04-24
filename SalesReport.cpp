#include "SalesReport.h"
#include <iostream>
#include <fstream>

using namespace std;
Transaction::Transaction(string d, int id, double amt)
    : date(d), receiptID(id), totalAmount(amt) {
}

double Transaction::getAmount() const {
    return totalAmount;
}

string Transaction::getDate() const {
    return date;
}

bool Transaction::readFromFile(ifstream& file) {
    if (file >> date >> receiptID >> totalAmount) {
        return true;
    }
    return false; 
}

void Transaction::display() const {
    cout << date << "\t" << receiptID << "\t\t$" << totalAmount << endl;
}

BillingSystem::BillingSystem(string f) : filename(f) {}

void BillingSystem::processSale(string date, int receiptID, double amount) {
    // ios::app ensures it creates the file if it doesn't exist
    ofstream file(filename, ios::app);

    if (file.is_open()) {
        file << date << " " << receiptID << " " << amount << "\n";
        file.close();
        cout << "[Success] Sale saved to file! (Receipt: " << receiptID << ")" << endl;
    }
    else {
        cout << "[Error] Could not open file to save sale." << endl;
    }
}
ReportGenerator::ReportGenerator(string f) : filename(f) {}

void ReportGenerator::generateTotalSalesReport() {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No sales data found. (File doesn't exist yet!)" << endl;
        return;
    }

    Transaction temp; 
    double totalRevenue = 0.0;
    int totalTransactions = 0;
    cout << "\n=======================================" << endl;
    cout << "          TOTAL SALES REPORT           " << endl;
    cout << "=======================================" << endl;
    cout << "Date\t\tReceipt ID\tAmount" << endl;
    cout << "---------------------------------------" << endl;
    while (temp.readFromFile(file)) {
        temp.display();
        totalRevenue += temp.getAmount();
        totalTransactions++;
    }
    file.close();
    cout << "---------------------------------------" << endl;
    cout << "Total Transactions: " << totalTransactions << endl;
    cout << "Total Revenue:      $" << totalRevenue << endl;
    cout << "=======================================\n" << endl;
}