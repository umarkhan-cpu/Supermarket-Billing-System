#include <iostream>
#include "Cashier/Refund.h"
#include "Cashier/RefundManagement.h"
using namespace std;

int main() {
    cout << "===== RefundManagement Test =====\n\n";

    // --- Test 1: Load from file ---
    cout << "Loading from file...\n";
    RefundManagement::loadFromFile();
    cout << "Loaded " << RefundManagement::getCount() << " refunds.\n\n";

    // --- Test 2: Create valid refunds ---
    cout << "Creating refunds:\n";
    cout << "  Txn 42, 'Damaged item', Rs. 250:        "
        << (RefundManagement::createRefund(42, "Damaged item", 250) ? "OK" : "FAILED") << "\n";
    cout << "  Txn 17, 'Wrong size', Rs. 1500:         "
        << (RefundManagement::createRefund(17, "Wrong size", 1500) ? "OK" : "FAILED") << "\n";
    cout << "  Txn 42, 'Defective again', Rs. 100:     "
        << (RefundManagement::createRefund(42, "Defective again", 100) ? "OK" : "FAILED") << "\n\n";

    // --- Test 3: Invalid refunds (all should fail) ---
    cout << "Creating invalid refunds (all should FAIL):\n";
    cout << "  Negative txnID:                  "
        << (RefundManagement::createRefund(-5, "Test", 100) ? "OK" : "FAILED (expected)") << "\n";
    cout << "  Zero txnID:                      "
        << (RefundManagement::createRefund(0, "Test", 100) ? "OK" : "FAILED (expected)") << "\n";
    cout << "  Empty reason:                    "
        << (RefundManagement::createRefund(50, "", 100) ? "OK" : "FAILED (expected)") << "\n";
    cout << "  Reason with comma:               "
        << (RefundManagement::createRefund(51, "Bad,Reason", 100) ? "OK" : "FAILED (expected)") << "\n";
    cout << "  Negative amount:                 "
        << (RefundManagement::createRefund(52, "Test", -50) ? "OK" : "FAILED (expected)") << "\n";
    cout << "  Zero amount:                     "
        << (RefundManagement::createRefund(53, "Test", 0) ? "OK" : "FAILED (expected)") << "\n\n";

    // --- Test 4: View all ---
    cout << "After valid creates, count = " << RefundManagement::getCount()
        << " (expected 3)\n";
    RefundManagement::viewAll();

    // --- Test 5: viewByTransactionID ---
    cout << "\nRefunds for transaction 42 (expected 2 rows):";
    RefundManagement::viewByTransactionID(42);

    cout << "\nRefunds for transaction 17 (expected 1 row):";
    RefundManagement::viewByTransactionID(17);

    cout << "\nRefunds for transaction 999 (expected: none):\n";
    RefundManagement::viewByTransactionID(999);

    // --- Test 6: findByID ---
    cout << "\nfindByID tests:\n";
    Refund r1 = RefundManagement::findByID(1);
    cout << "  ID 1: txnID=" << r1.getTransactionID()
        << ", reason='" << r1.getReason()
        << "', amount=" << r1.getAmount()
        << ", date=" << r1.getDate() << "\n";

    Refund r999 = RefundManagement::findByID(999);
    cout << "  ID 999: getID() = " << r999.getID() << " (expected 0 — not found)\n";

    // --- Test 7: ID continuity (no reuse, even after the file persists) ---
    cout << "\nAdding another refund - should get next sequential ID:\n";
    RefundManagement::createRefund(100, "Test continuity", 50);
    cout << "  Latest refund's ID: " << RefundManagement::findByID(4).getID()
        << " (expected 4)\n";

    // --- Test 8: Today's date stamping ---
    cout << "\nDate on most recent refund: "
        << RefundManagement::findByID(4).getDate()
        << " (should be today's actual date)\n";

    // --- Test 9: Cleanup ---
    cout << "\nCleaning up...\n";
    RefundManagement::cleanup();
    cout << "Count after cleanup: " << RefundManagement::getCount()
        << " (expected 0)\n";

    cout << "\n===== All tests complete =====\n";
    return 0;
}