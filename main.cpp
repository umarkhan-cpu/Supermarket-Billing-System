#include "Cashier/Transaction.h"
#include "Cashier/TransactionManagement.h"
#include "Cashier/TransactionManagement.h"
#include "Cashier/RefundManagement.h"
#include "Admin/Product.h"
#include "Admin/ProductManagement.h"
#include "Admin/InventoryManagement.h"
#include "SalesReport.h"
#include <iostream>
using namespace std;

int main() {

    // Load existing data
    TransactionManagement::loadFromFile();

    cout << "\n=== BEFORE ADDING NEW DATA ===\n";
    TransactionManagement::viewHistory();

    // Create transactions using YOUR actual constructor
    Transaction t1, t2, t3;

    t1.setData(1, "2026-04-28", 101, 500.0, "Completed");
    t2.setData(2, "2026-04-28", 102, 1200.0, "Completed");
    t3.setData(3, "2026-04-27", 103, 800.0, "Completed");

    // Add transactions
    TransactionManagement::addTransaction(t1);
    TransactionManagement::addTransaction(t2);
    TransactionManagement::addTransaction(t3);

    cout << "\n=== AFTER ADDING ===\n";
    TransactionManagement::viewHistory();

    // Test search by ID
    cout << "\n=== SEARCH ID 2 ===\n";
    Transaction result = TransactionManagement::searchByID(2);
    result.show();   // you already have show()

    // Test search by date
    cout << "\n=== SEARCH DATE 2026-04-28 ===\n";
    TransactionManagement::searchByDate("2026-04-28");

    // Test refund
    cout << "\n=== REFUND TEST (ID 1) ===\n";
    if (TransactionManagement::markAsRefunded(1))
        cout << "Refund successful\n";
    else
        cout << "Refund failed\n";

    // Test report
    cout << "\n=== GENERATING REPORT ===\n";
    SalesReport report("sales_report.txt");
    report.generatetotalsalesreport();

    // Save data
    TransactionManagement::saveToFile();

    // Cleanup memory
    TransactionManagement::cleanup();

    cout << "\n=== DONE ===\n";

    return 0;
}