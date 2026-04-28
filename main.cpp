#include "Cashier/Transaction.h"
#include "Cashier/TransactionManagement.h"
#include "Cashier/RefundManagement.h"
#include "Admin/Product.h"
#include "Admin/ProductManagement.h"
#include "Admin/InventoryManagement.h"
#include <iostream>
#include "Transaction.h"
#include "TransactionManagement.h"
#include "SalesReport.h"

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

int main() {
    // Setup
    TransactionManagement::loadFromFile();
    RefundManagement::loadFromFile();
    ProductManagement::loadFromFile();
    InventoryManagement::loadFromFile();

    // Create test data
    ProductManagement::addProduct("TestProduct", 1, 100.0, 50);  // 50 in stock

    Transaction t;
    t.setData(1, "2026-04-28", 101, 1000.0, "Completed");
    TransactionManagement::addTransaction(t);
    TransactionManagement::saveToFile();

    // Find the test product's ID (auto-assigned)
    int testProductID = ProductManagement::getCount() > 0
        ? ProductManagement::getAt(0).getID() : 0;

    int stockBefore = ProductManagement::findByID(testProductID).getStock();
    cout << "Stock before refund: " << stockBefore << endl;  // 50

    // Test 1: Invalid productID → fail
    cout << "Test 1 (bad product): "
        << RefundManagement::createRefund(1, "Damaged", 100, 999, 1) << endl;  // 0

    // Test 2: Negative quantity → fail
    cout << "Test 2 (bad qty): "
        << RefundManagement::createRefund(1, "Damaged", 100, testProductID, -1) << endl;  // 0

    // Test 3: Valid refund with restock → success
    cout << "Test 3 (valid): "
        << RefundManagement::createRefund(1, "Defective", 100, testProductID, 3) << endl;  // 1

    // Test 4: Verify stock increased by 3
    int stockAfter = ProductManagement::findByID(testProductID).getStock();
    cout << "Stock after refund: " << stockAfter << endl;  // 53

    // Test 5: Verify transaction marked refunded
    Transaction after = TransactionManagement::searchByID(1);
    cout << "Transaction status: " << after.getStatus() << endl;  // Refunded

    InventoryManagement::cleanup();
    ProductManagement::cleanup();
    RefundManagement::cleanup();
    TransactionManagement::cleanup();

    return 0;
}