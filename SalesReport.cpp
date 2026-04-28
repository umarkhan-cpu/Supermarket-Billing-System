#include "SalesReport.h"
#include "TransactionManagement.h"
#include <iostream>
using namespace std;
SalesReport::SalesReport(string f) : filename(f) {}
void SalesReport::generatetotalsalesreport() {

    TransactionManagement::loadFromFile();
    int totalTransactions = TransactionManagement::getCount();

    if (totalTransactions == 0) {
        cout << "No sales data found." << endl;
        return;
    }
    double totalRevenue = 0.0;
    int validSales = 0;
    cout << endl;
    cout << "          TOTAL SALES REPORT           " << endl;
    cout <<  endl;
    for (int i = 0; i < totalTransactions; i++) {
        Transaction temp = TransactionManagement::getByIndex(i);
        if (temp.getStatus() != "Refunded") {
            totalRevenue += temp.getTotalAmount();
            validSales++;
        }
    }
    cout << "Total Valid Sales: " << validSales << endl;
    cout << "Total Revenue:     " << totalRevenue << endl;
    cout << "=======================================\n" << endl;
}