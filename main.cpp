// =====================================================================
//  Supermarket Billing System - Backend Bootstrap & Smoke Test Utility
//  CS1004 Object Oriented Programming
//  FAST-NUCES Lahore, Section A, Group 10
//
//  This is the console entry point for the Supermarket-Billing-System
//  project. The actual user-facing application is the WinForms GUI
//  (supermarketui project). This console binary exists for two reasons:
//
//  1. BOOTSTRAP - seeds Data/users.txt with default Admin and Cashier
//     accounts so the GUI has something to log in with. If the file
//     is wiped or never created, this rebuilds it.
//
//  2. SMOKE TEST - runs every backend manager (Category, Product,
//     Inventory, Discount, Refund, Transaction, Sales Report, Session)
//     through their core operations and reports pass/fail. This
//     catches regressions before they reach the GUI.
//
//  Run order during demos:
//     1. Build supermarketui project
//     2. Run THIS console binary first (option 1 + 2) to seed data
//        and confirm everything links and loads correctly
//     3. Then launch the GUI
//
//  Maintained by:  Muhammad Umar Khan (Team Lead, 25L-3089)
// =====================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "Common/User.h"
#include "Common/SessionManager.h"
#include "Admin/Admin.h"
#include "Admin/UserManagement.h"
#include "Admin/Category.h"
#include "Admin/CategoryManagement.h"
#include "Admin/Product.h"
#include "Admin/ProductManagement.h"
#include "Admin/Inventory.h"
#include "Admin/InventoryManagement.h"
#include "Admin/SalesReport.h"
#include "Cashier/Cashier.h"
#include "Cashier/Discount.h"
#include "Cashier/DiscountManagement.h"
#include "Cashier/Refund.h"
#include "Cashier/RefundManagement.h"
#include "Cashier/Transaction.h"
#include "Cashier/TransactionManagement.h"

using namespace std;

// ----- Console formatting helpers (kept tiny and dependency-free) -----

static void printBanner() {
    cout << "\n";
    cout << "============================================================\n";
    cout << "  SUPERMARKET BILLING SYSTEM - Backend Console Utility\n";
    cout << "  CS1004 OOP   |   FAST-NUCES Lahore   |   Group 10\n";
    cout << "============================================================\n";
}

static void printSection(const string& title) {
    cout << "\n--- " << title << " ---\n";
}

// Pretty pass/fail line. Tracks total/passed across an entire run so the
// menu can report a final tally.
static int g_totalChecks = 0;
static int g_passedChecks = 0;

static void check(const string& label, bool passed) {
    g_totalChecks++;
    if (passed) g_passedChecks++;
    cout << "  [" << (passed ? "PASS" : "FAIL") << "]  " << label << "\n";
}

static void resetCheckCounter() {
    g_totalChecks = 0;
    g_passedChecks = 0;
}

// =====================================================================
//  OPTION 1 - BOOTSTRAP DEFAULT USERS
// =====================================================================
//  Writes 5 accounts to Data/users.txt if they don't already exist:
//  This is the recovery procedure documented in the README - if all
//  admin accounts are accidentally deleted, run option 1 to restore.
// =====================================================================

static bool userAlreadyExists(const string& target) {
    ifstream in("Data/users.txt");
    if (!in.is_open()) return false;
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        // CSV format: id,username,hash,role
        size_t firstComma = line.find(',');
        if (firstComma == string::npos) continue;
        size_t secondComma = line.find(',', firstComma + 1);
        if (secondComma == string::npos) continue;
        string username = line.substr(firstComma + 1, secondComma - firstComma - 1);
        if (username == target) return true;
    }
    return false;
}

static void seedUser(const string& username, const string& plainPassword, const string& role) {
    if (userAlreadyExists(username)) {
        cout << "  [SKIP]  " << username << " already exists\n";
        return;
    }

    UserManagement um;  // nextAvailableID is an instance method, so we need an object
    int id = um.nextAvailableID();
    string hash = UserManagement::hashedpass(plainPassword);  // hashedpass IS static, leave as-is

    ofstream out("Data/users.txt", ios::app);
    if (!out.is_open()) {
        cout << "  [FAIL]  Could not open Data/users.txt for writing\n";
        return;
    }
    out << id << "," << username << "," << hash << "," << role << "\n";
    out.close();
    cout << "  [DONE]  Seeded " << username << " (" << role << ")\n";
}

static void bootstrapUsers() {
    printSection("Bootstrap: Default User Accounts");
    cout << "Seeding default accounts into Data/users.txt...\n\n";

    seedUser("Admin", "admin123", "Admin");
    seedUser("Umar", "umar123", "Cashier");
    seedUser("Mahnoor", "mahnoor123", "Cashier");
    seedUser("Farda", "farda123", "Cashier");
    seedUser("Areesha", "areesha123", "Cashier");

    cout << "\nSeeded 5 accounts (1 Admin + 4 Cashiers).\n";
    cout << "Team members can log in with their personal credentials.\n";
    cout << "For demo/grader access: use 'Admin' / 'admin123'\n";
}

// =====================================================================
//  OPTION 2 - BACKEND SMOKE TEST
// =====================================================================
//  Runs every manager class through a load -> read -> count cycle.
//  This is non-destructive: no records are added, edited, or deleted.
//  The goal is to catch file-format issues, parser crashes, and link
//  errors before the GUI tries to do the same operations.
// =====================================================================

static void smokeTestCategoryManager() {
    printSection("Smoke Test: CategoryManagement");
    try {
        CategoryManagement::loadFromFile();
        check("CategoryManagement::loadFromFile() did not throw", true);
        cout << "  [INFO]  Loaded " << CategoryManagement::getCount() << " categories\n";
        CategoryManagement::cleanup();
        check("CategoryManagement::cleanup() ran cleanly", true);
    }
    catch (const exception& e) {
        check(string("CategoryManagement crashed: ") + e.what(), false);
    }
}

static void smokeTestProductManager() {
    printSection("Smoke Test: ProductManagement");
    try {
        ProductManagement::loadFromFile();
        check("ProductManagement::loadFromFile() did not throw", true);
        cout << "  [INFO]  Loaded " << ProductManagement::getCount() << " products\n";
        ProductManagement::cleanup();
        check("ProductManagement::cleanup() ran cleanly", true);
    }
    catch (const exception& e) {
        check(string("ProductManagement crashed: ") + e.what(), false);
    }
}

static void smokeTestInventoryManager() {
    printSection("Smoke Test: InventoryManagement");
    try {
        // Inventory depends on ProductManagement being loaded first, since
        // stock figures live on Product records. We re-load here to keep
        // each smoke test independent.
        ProductManagement::loadFromFile();
        InventoryManagement::loadFromFile();
        check("InventoryManagement::loadFromFile() did not throw", true);
        // Note: InventoryManagement does not expose a public getCount() - the
        // count is private and only used internally. Loading without throwing
        // is sufficient evidence that the file format and parser are healthy.
        InventoryManagement::cleanup();
        ProductManagement::cleanup();
        check("InventoryManagement::cleanup() ran cleanly", true);
    }
    catch (const exception& e) {
        check(string("InventoryManagement crashed: ") + e.what(), false);
    }
}

static void smokeTestDiscountManager() {
    printSection("Smoke Test: DiscountManagement");
    try {
        DiscountManagement::loadFromFile();
        check("DiscountManagement::loadFromFile() did not throw", true);
        cout << "  [INFO]  Loaded " << DiscountManagement::getCount() << " coupons\n";
        DiscountManagement::cleanup();
        check("DiscountManagement::cleanup() ran cleanly", true);
    }
    catch (const exception& e) {
        check(string("DiscountManagement crashed: ") + e.what(), false);
    }
}

static void smokeTestTransactionManager() {
    printSection("Smoke Test: TransactionManagement");
    try {
        TransactionManagement::loadFromFile();
        check("TransactionManagement::loadFromFile() did not throw", true);
        cout << "  [INFO]  Loaded " << TransactionManagement::getCount() << " transactions\n";
        TransactionManagement::cleanup();
        check("TransactionManagement::cleanup() ran cleanly", true);
    }
    catch (const exception& e) {
        check(string("TransactionManagement crashed: ") + e.what(), false);
    }
}

static void smokeTestRefundManager() {
    printSection("Smoke Test: RefundManagement");
    try {
        RefundManagement::loadFromFile();
        check("RefundManagement::loadFromFile() did not throw", true);
        cout << "  [INFO]  Loaded " << RefundManagement::getCount() << " refunds\n";
        RefundManagement::cleanup();
        check("RefundManagement::cleanup() ran cleanly", true);
    }
    catch (const exception& e) {
        check(string("RefundManagement crashed: ") + e.what(), false);
    }
}

static void smokeTestSession() {
    printSection("Smoke Test: SessionManager + Polymorphism");
    try {
        // Build an Admin and a Cashier on the heap and verify polymorphic
        // dispatch through the User base pointer. This is the same pattern
        // the GUI uses to track who is logged in.
        User* a = new Admin(999, "smoketest_admin", "x");
        User* c = new Cashier(998, "smoketest_cashier", "x");

        check("Admin->getRoleName() == \"Admin\"", a->getRoleName() == "Admin");
        check("Cashier->getRoleName() == \"Cashier\"", c->getRoleName() == "Cashier");

        SessionManager::startSession(a);
        check("SessionManager recognizes Admin", SessionManager::isAdmin());
        check("SessionManager rejects Cashier when Admin is current", !SessionManager::isCashier());

        SessionManager::endSession();
        SessionManager::startSession(c);
        check("SessionManager recognizes Cashier", SessionManager::isCashier());

        SessionManager::endSession();
        // SessionManager::endSession deletes the user pointer it was tracking,
        // so we don't need to delete `c` ourselves. We do still own `a`.
        delete a;
    }
    catch (const exception& e) {
        check(string("SessionManager smoke test crashed: ") + e.what(), false);
    }
}

static void runAllSmokeTests() {
    resetCheckCounter();
    cout << "\nRunning full backend smoke test...\n";

    smokeTestCategoryManager();
    smokeTestProductManager();
    smokeTestInventoryManager();
    smokeTestDiscountManager();
    smokeTestTransactionManager();
    smokeTestRefundManager();
    smokeTestSession();

    printSection("Summary");
    cout << "  " << g_passedChecks << " / " << g_totalChecks << " checks passed.\n";
    if (g_passedChecks == g_totalChecks) {
        cout << "  Backend is healthy. Safe to launch the GUI.\n";
    }
    else {
        cout << "  Some checks failed. Investigate before demoing.\n";
    }
}

// =====================================================================
//  OPTION 3 - QUICK DATA SUMMARY
// =====================================================================
//  Loads every data file and prints record counts. Useful for a fast
//  "what's in the database right now?" sanity check before a demo.
// =====================================================================

static void dataSummary() {
    printSection("Data Summary");

    CategoryManagement::loadFromFile();
    cout << "  Categories:   " << CategoryManagement::getCount() << "\n";
    CategoryManagement::cleanup();

    ProductManagement::loadFromFile();
    cout << "  Products:     " << ProductManagement::getCount() << "\n";
    ProductManagement::cleanup();

    DiscountManagement::loadFromFile();
    cout << "  Coupons:      " << DiscountManagement::getCount() << "\n";
    DiscountManagement::cleanup();

    TransactionManagement::loadFromFile();
    cout << "  Transactions: " << TransactionManagement::getCount() << "\n";
    TransactionManagement::cleanup();

    RefundManagement::loadFromFile();
    cout << "  Refunds:      " << RefundManagement::getCount() << "\n";
    RefundManagement::cleanup();

    // Users are stored as raw lines, not via a manager class - so we just
    // count non-blank lines in the file directly.
    int userCount = 0;
    ifstream uf("Data/users.txt");
    string line;
    while (getline(uf, line)) {
        if (!line.empty()) userCount++;
    }
    cout << "  Users:        " << userCount << "\n";
}

// =====================================================================
//  MAIN MENU
// =====================================================================

static void printMenu() {
    cout << "\n------------------------------------------------------------\n";
    cout << "  Choose an option:\n";
    cout << "    1. Bootstrap default user accounts\n";
    cout << "    2. Run full backend smoke test\n";
    cout << "    3. Show data summary (record counts)\n";
    cout << "    4. Bootstrap + smoke test (recommended for demo)\n";
    cout << "    0. Exit\n";
    cout << "------------------------------------------------------------\n";
    cout << "  Selection: ";
}

int main() {
    printBanner();
    cout << "\nThis console utility seeds default accounts and runs\n";
    cout << "non-destructive backend health checks. The actual user-\n";
    cout << "facing application is the supermarketui WinForms project.\n";

    int choice = -1;
    while (choice != 0) {
        printMenu();
        if (!(cin >> choice)) {
            // Bad input - clear the stream and prompt again rather than crash
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "  Invalid input. Please enter a number 0-4.\n";
            continue;
        }

        switch (choice) {
        case 1:
            bootstrapUsers();
            break;
        case 2:
            runAllSmokeTests();
            break;
        case 3:
            dataSummary();
            break;
        case 4:
            bootstrapUsers();
            runAllSmokeTests();
            break;
        case 0:
            cout << "\nGoodbye.\n";
            break;
        default:
            cout << "  Unknown option. Please pick 0-4.\n";
        }
    }

    return 0;
}