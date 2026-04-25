#include <iostream>
#include "Admin/Category.h"
#include "Admin/CategoryManagement.h"
using namespace std;

int main() {
    cout << "===== CategoryManagement Test =====\n\n";

    // --- Test 1: Load from file (creates Data/categories.txt if missing) ---
    cout << "Loading from file...\n";
    CategoryManagement::loadFromFile();
    cout << "Loaded " << CategoryManagement::getCount() << " categories.\n\n";

    // --- Test 2: Add categories ---
    cout << "Adding categories:\n";
    cout << "  Add 'Dairy' / 'Milk and cheese': "
        << (CategoryManagement::addCategory("Dairy", "Milk and cheese") ? "OK" : "FAILED") << "\n";
    cout << "  Add 'Bakery' / 'Bread products':  "
        << (CategoryManagement::addCategory("Bakery", "Bread products") ? "OK" : "FAILED") << "\n";
    cout << "  Add 'Beverages' / 'Drinks':       "
        << (CategoryManagement::addCategory("Beverages", "Drinks") ? "OK" : "FAILED") << "\n";
    cout << "  Add empty name (should fail):     "
        << (CategoryManagement::addCategory("", "test") ? "OK" : "FAILED (expected)") << "\n";
    cout << "  Add name with comma (should fail):"
        << (CategoryManagement::addCategory("Bad,Name", "test") ? "OK" : "FAILED (expected)") << "\n\n";

    // --- Test 3: View all ---
    CategoryManagement::viewAll();

    // --- Test 4: Edit a category ---
    cout << "\nEditing ID 2 -> 'Bakery & Pastries' / 'Fresh bread':\n";
    cout << "  Result: "
        << (CategoryManagement::editCategory(2, "Bakery & Pastries", "Fresh bread") ? "OK" : "FAILED") << "\n";
    cout << "  Edit nonexistent ID 999 (should fail): "
        << (CategoryManagement::editCategory(999, "x", "y") ? "OK" : "FAILED (expected)") << "\n";

    CategoryManagement::viewAll();

    // --- Test 5: findByID ---
    cout << "\nfindByID(1): " << CategoryManagement::findByID(1).getName() << "\n";
    cout << "findByID(999) - getID() returns: " << CategoryManagement::findByID(999).getID()
        << " (expected 0)\n";

    // --- Test 6: Delete ---
    cout << "\nDeleting ID 1:\n";
    cout << "  Result: " << (CategoryManagement::deleteCategory(1) ? "OK" : "FAILED") << "\n";
    cout << "  Delete nonexistent ID 999 (should fail): "
        << (CategoryManagement::deleteCategory(999) ? "OK" : "FAILED (expected)") << "\n";

    CategoryManagement::viewAll();

    // --- Test 7: nextAvailableID after delete ---
    cout << "\nAdding new category after delete (should get a fresh ID, not reuse 1):\n";
    CategoryManagement::addCategory("Snacks", "Chips and biscuits");
    CategoryManagement::viewAll();

    // --- Test 8: cleanup ---
    cout << "\nCleaning up...\n";
    CategoryManagement::cleanup();
    cout << "Count after cleanup: " << CategoryManagement::getCount() << " (expected 0)\n";

    cout << "\n===== All tests complete =====\n";
    return 0;
}