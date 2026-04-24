#include<iostream>
#include<string>
#include"SalesReport.h"
int main() {
    string myFile = "transactions.txt";

    BillingSystem cashier(myFile);
    ReportGenerator admin(myFile);

    cout << "--- SUPERMARKET BILLING SYSTEM ---\n" << endl;

    cashier.processSale("2026-04-24", 1001, 45.50);
    cashier.processSale("2026-04-24", 1002, 120.75);
    cashier.processSale("2026-04-25", 1003, 15.00);

    admin.generateTotalSalesReport();

    return 0;
}

