// Test main for SessionManager
// Demonstrates: defensive nulls, session lifecycle, activity tracking, real timeout

#include "Common/User.h"
#include "Common/SessionManager.h"
#include "Admin/Admin.h"
#include "Cashier/Cashier.h"

#include <iostream>
#include <thread>      // for std::this_thread::sleep_for
#include <chrono>      // for std::chrono::seconds

using namespace std;

// Helper to make output cleaner
void divider(const string& label) {
    cout << "\n========== " << label << " ==========\n";
}

void status() {
    User* u = SessionManager::getCurrentUser();
    cout << "  currentUser:        " << (u ? u->getUsername() : "(nullptr)") << "\n";
    cout << "  sessionDuration:    " << SessionManager::getSessionDuration() << "s\n";
    cout << "  secondsRemaining:   " << SessionManager::getSecondsRemaining() << "s\n";
    cout << "  checkTimeout():     " << (SessionManager::checkTimeout() ? "TRUE (session expired)" : "false (session active)") << "\n";
}

int main() {
    cout << "==========================================\n";
    cout << "    SESSION MANAGER TEST SUITE\n";
    cout << "==========================================\n";

    // ------------------------------------------------------------
    // TEST 1: Defensive checks before any session exists
    // ------------------------------------------------------------
    divider("TEST 1: No session - defensive checks");
    status();
    cout << "\nExpected: nullptr, 0s, 0s, false\n";

    // updateActivity should be a safe no-op
    SessionManager::updateActivity();
    cout << "After updateActivity() with no session: no crash. PASS.\n";

    // endSession should be a safe no-op
    SessionManager::endSession();
    cout << "After endSession() with no session: no crash. PASS.\n";

    // ------------------------------------------------------------
    // TEST 2: startSession with nullptr should reject
    // ------------------------------------------------------------
    divider("TEST 2: startSession(nullptr)");
    bool result = SessionManager::startSession(nullptr);
    cout << "startSession(nullptr) returned: " << (result ? "true (BUG!)" : "false (correct)") << "\n";

    // ------------------------------------------------------------
    // TEST 3: Normal session start with an Admin
    // ------------------------------------------------------------
    divider("TEST 3: Start session with Admin");
    User* admin = new Admin(1, "Umar", "abc123");
    result = SessionManager::startSession(admin);
    cout << "startSession returned: " << (result ? "true (correct)" : "false (BUG!)") << "\n\n";
    status();
    cout << "\nExpected: 'Umar', 0s (just started), ~600s, false\n";

    // ------------------------------------------------------------
    // TEST 4: Polymorphic access through SessionManager
    // ------------------------------------------------------------
    divider("TEST 4: Polymorphism - call showDashboard via SessionManager");
    User* current = SessionManager::getCurrentUser();
    if (current) current->showDashboard();

    // ------------------------------------------------------------
    // TEST 5: Wait 3 seconds, check duration ticks up
    // ------------------------------------------------------------
    divider("TEST 5: Sleep 3 seconds - duration should increase");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    status();
    cout << "\nExpected: duration ~3s, remaining ~597s\n";

    // ------------------------------------------------------------
    // TEST 6: updateActivity resets the inactivity timer
    // ------------------------------------------------------------
    divider("TEST 6: updateActivity() resets remaining time");
    SessionManager::updateActivity();
    status();
    cout << "\nExpected: duration still ~3s (login was 3s ago),\n";
    cout << "          remaining back to ~600s (activity reset)\n";

    // ------------------------------------------------------------
    // TEST 7: Replacement semantics - startSession with new user ends old
    // ------------------------------------------------------------
    divider("TEST 7: Replacement semantics");
    User* cashier = new Cashier(2, "Ahmad", "xyz789");
    SessionManager::startSession(cashier);
    cout << "After startSession(cashier):\n";
    status();
    cout << "\nExpected: currentUser is now 'Ahmad', durations reset\n";

    // ------------------------------------------------------------
    // TEST 8: ACTUAL TIMEOUT TEST
    // ------------------------------------------------------------
    divider("TEST 8: Timeout");
    cout << "To verify timeout actually fires:\n";
    cout << "  1. In SessionManager.cpp, change timeoutLimit = 600 to 3\n";
    cout << "  2. Rebuild and run again\n";
    cout << "  3. Sleep 4 seconds below - should report TIMEOUT\n";
    cout << "  4. Change it back to 600 when done\n\n";

    cout << "Sleeping 4 seconds...\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));
    status();
    cout << "\nIf timeoutLimit is 3: should show 'TRUE (expired)'\n";
    cout << "If timeoutLimit is 600: still 'false (session active)'\n";

    // ------------------------------------------------------------
    // TEST 9: Clean shutdown
    // ------------------------------------------------------------
    divider("TEST 9: endSession");
    SessionManager::endSession();
    status();
    cout << "\nExpected: nullptr, 0s, 0s, false\n";

    // ------------------------------------------------------------
    // TEST 10: Role queries
    // ------------------------------------------------------------
    divider("TEST 10: Role queries");
    
    // Currently no session (we ended it in Test 9)
    cout << "No session - isAdmin: "   << (SessionManager::isAdmin()   ? "true (BUG!)" : "false (correct)") << "\n";
    cout << "No session - isCashier: " << (SessionManager::isCashier() ? "true (BUG!)" : "false (correct)") << "\n";
    
    // Start an Admin session
    SessionManager::startSession(admin);
    cout << "\nWith Admin session:\n";
    cout << "  isAdmin:   " << (SessionManager::isAdmin()   ? "true (correct)" : "false (BUG!)") << "\n";
    cout << "  isCashier: " << (SessionManager::isCashier() ? "true (BUG!)" : "false (correct)") << "\n";
    
    // Switch to Cashier
    SessionManager::startSession(cashier);
    cout << "\nWith Cashier session:\n";
    cout << "  isAdmin:   " << (SessionManager::isAdmin()   ? "true (BUG!)" : "false (correct)") << "\n";
    cout << "  isCashier: " << (SessionManager::isCashier() ? "true (correct)" : "false (BUG!)") << "\n";
    
    SessionManager::endSession();

    cout << "\n==========================================\n";
    cout << "    ALL TESTS COMPLETE\n";
    cout << "==========================================\n";

    // Clean up the User objects (we own them, not SessionManager)
    delete admin;
    delete cashier;

    return 0;
}