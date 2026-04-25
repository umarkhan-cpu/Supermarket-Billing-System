#include <iostream>
#include "Cashier/Discount.h"
#include "Cashier/DiscountManagement.h"
using namespace std;

int main() {
    cout << "===== DiscountManagement Test =====\n\n";

    // --- Test 1: Load from file ---
    cout << "Loading from file...\n";
    DiscountManagement::loadFromFile();
    cout << "Loaded " << DiscountManagement::getCount() << " coupons.\n\n";

    // --- Test 2: Add valid coupons ---
    cout << "Adding coupons:\n";
    cout << "  SAVE20 (20% off):     "
        << (DiscountManagement::addCoupon("SAVE20", "PERCENTAGE", 20) ? "OK" : "FAILED") << "\n";
    cout << "  FLAT50 (Rs. 50 off):  "
        << (DiscountManagement::addCoupon("FLAT50", "FIXED", 50) ? "OK" : "FAILED") << "\n";
    cout << "  HALFOFF (50% off):    "
        << (DiscountManagement::addCoupon("HALFOFF", "PERCENTAGE", 50) ? "OK" : "FAILED") << "\n\n";

    // --- Test 3: Add invalid coupons (should all fail) ---
    cout << "Adding invalid coupons (all should FAIL):\n";
    cout << "  Duplicate code SAVE20:        "
        << (DiscountManagement::addCoupon("SAVE20", "FIXED", 30) ? "OK" : "FAILED (expected)") << "\n";
    cout << "  Invalid type FOOBAR:          "
        << (DiscountManagement::addCoupon("BAD1", "FOOBAR", 10) ? "OK" : "FAILED (expected)") << "\n";
    cout << "  Negative value:               "
        << (DiscountManagement::addCoupon("BAD2", "FIXED", -5) ? "OK" : "FAILED (expected)") << "\n";
    cout << "  Percentage > 100:             "
        << (DiscountManagement::addCoupon("BAD3", "PERCENTAGE", 150) ? "OK" : "FAILED (expected)") << "\n";
    cout << "  Code with space:              "
        << (DiscountManagement::addCoupon("BAD CODE", "FIXED", 10) ? "OK" : "FAILED (expected)") << "\n";
    cout << "  Empty code:                   "
        << (DiscountManagement::addCoupon("", "FIXED", 10) ? "OK" : "FAILED (expected)") << "\n\n";

    // --- Test 4: View all ---
    DiscountManagement::viewAll();

    // --- Test 5: applyCoupon — the integration contract ---
    cout << "\nApplying coupons to a Rs. 1000 subtotal:\n";
    cout << "  SAVE20 (20%):    discount = Rs. " << DiscountManagement::applyCoupon("SAVE20", 1000)
        << " (expected 200)\n";
    cout << "  FLAT50 (Rs. 50): discount = Rs. " << DiscountManagement::applyCoupon("FLAT50", 1000)
        << " (expected 50)\n";
    cout << "  HALFOFF (50%):   discount = Rs. " << DiscountManagement::applyCoupon("HALFOFF", 1000)
        << " (expected 500)\n";

    cout << "\nApplying coupons to a Rs. 30 subtotal:\n";
    cout << "  FLAT50 on Rs. 30 bill: discount = Rs. " << DiscountManagement::applyCoupon("FLAT50", 30)
        << " (expected 30 — capped, not 50)\n";

    cout << "\nApplying invalid codes:\n";
    cout << "  Nonexistent code:        " << DiscountManagement::applyCoupon("NOPE", 1000)
        << " (expected 0)\n";

    // --- Test 6: setActive — deactivate then reapply ---
    cout << "\nDeactivating SAVE20 (ID 1):\n";
    cout << "  Result: " << (DiscountManagement::setActive(1, false) ? "OK" : "FAILED") << "\n";
    cout << "  Apply SAVE20 after deactivation: " << DiscountManagement::applyCoupon("SAVE20", 1000)
        << " (expected 0)\n";

    cout << "\nReactivating SAVE20:\n";
    cout << "  Result: " << (DiscountManagement::setActive(1, true) ? "OK" : "FAILED") << "\n";
    cout << "  Apply SAVE20 after reactivation: " << DiscountManagement::applyCoupon("SAVE20", 1000)
        << " (expected 200)\n";

    // --- Test 7: Edit coupon ---
    cout << "\nEditing SAVE20 (ID 1) -> 25% off:\n";
    cout << "  Result: " << (DiscountManagement::editCoupon(1, "PERCENTAGE", 25) ? "OK" : "FAILED") << "\n";
    cout << "  Apply SAVE20 after edit: " << DiscountManagement::applyCoupon("SAVE20", 1000)
        << " (expected 250)\n";
    cout << "  Edit nonexistent ID 999 (should fail): "
        << (DiscountManagement::editCoupon(999, "FIXED", 100) ? "OK" : "FAILED (expected)") << "\n";

    DiscountManagement::viewAll();

    // --- Test 8: Delete ---
    cout << "\nDeleting ID 2 (FLAT50):\n";
    cout << "  Result: " << (DiscountManagement::deleteCoupon(2) ? "OK" : "FAILED") << "\n";
    cout << "  Apply FLAT50 after delete: " << DiscountManagement::applyCoupon("FLAT50", 1000)
        << " (expected 0)\n";

    DiscountManagement::viewAll();

    // --- Test 9: ID continuity after delete ---
    cout << "\nAdding new coupon NEWCODE after delete (should get fresh ID, not reuse 2):\n";
    DiscountManagement::addCoupon("NEWCODE", "FIXED", 75);
    DiscountManagement::viewAll();

    // --- Test 10: cleanup ---
    cout << "\nCleaning up...\n";
    DiscountManagement::cleanup();
    cout << "Count after cleanup: " << DiscountManagement::getCount() << " (expected 0)\n";

    cout << "\n===== All tests complete =====\n";
    return 0;
}