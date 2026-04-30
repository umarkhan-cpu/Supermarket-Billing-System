#include "Cashier/Transaction.h"
#include "Cashier/TransactionManagement.h"
#include "Cashier/RefundManagement.h"
#include "Admin/Product.h"
#include "Admin/ProductManagement.h"
#include "Admin/InventoryManagement.h"
#include <iostream>
using namespace std;

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
