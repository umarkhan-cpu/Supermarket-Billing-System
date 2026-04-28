#include "Cashier.h"
#include <iostream>
using namespace std;

// ============================================================================
// Constructors
// ============================================================================

Cashier::Cashier() : User()
{
    role = "Cashier";
}

Cashier::Cashier(int id, const string& uname, const string& pHash)
    : User(id, uname, pHash, "Cashier") {}

Cashier::Cashier(const Cashier& other) : User(other) {}

// ============================================================================
// Override pure virtual methods
// ============================================================================

void Cashier::showDashboard() // Only for console
{
    cout << "\n=========================================\n";
    cout << "         CASHIER DASHBOARD\n";
    cout << "=========================================\n";
    cout << "Welcome, " << username << "!\n";
    cout << "Last login: " << (lastLogin.empty() ? "First login" : lastLogin) << "\n";
    cout << "-----------------------------------------\n";
    cout << "1. New Bill / Checkout\n";
    cout << "2. Search & Filter Products\n";
    cout << "3. Apply Discount Coupon\n";
    cout << "4. Process Refund\n";
    cout << "5. View Transaction History\n";
    cout << "6. Logout\n";
    cout << "=========================================\n";
}

string Cashier::getRoleName() const
{
    return "Cashier";
}