#include "SalesReport.h"
#include "../Cashier/TransactionManagement.h"
#include "../Cashier/RefundManagement.h"
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

        // Modification by Umar (lead): To link 3 states of refund to sales report.
        // Net revenue: subtract any refunds against this transaction. This way
        // a partially-refunded transaction still contributes to revenue, but
        // only by the unrefunded portion. Fully-refunded transactions
        // contribute zero. Matches real retail accounting.
        float refunded = RefundManagement::getRefundedAmountForTransaction(temp.getID());
        totalRevenue += (temp.getTotalAmount() - refunded);

        // "Valid sales" = transactions with no refunds yet
        if (temp.getStatus() == "Completed") {
            validSales++;
        }
    }
    cout << "Total Valid Sales: " << validSales << endl;
    cout << "Total Revenue:     " << totalRevenue << endl;
    cout << "=======================================\n" << endl;
}