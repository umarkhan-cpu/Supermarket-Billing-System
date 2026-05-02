#include "Admin.h"
#include <iostream>
using namespace std;

// ============================================================================
// Constructors
// ============================================================================

Admin::Admin() : User()
{
    role = "Admin";
}

Admin::Admin(int id, const string& uname, const string& pHash)
    : User(id, uname, pHash, "Admin") {}

Admin::Admin(const Admin& other) : User(other) {}

// ============================================================================
// Override pure virtual methods
// ============================================================================

void Admin::showDashboard() // Only for console
{
    cout << "\n=========================================\n";
    cout << "         ADMIN DASHBOARD\n";
    cout << "=========================================\n";
    cout << "Welcome, " << username << "!\n";
    cout << "Last login: " << (lastLogin.empty() ? "First login" : lastLogin) << "\n";
    cout << "-----------------------------------------\n";
    cout << "1. Manage Users\n";
    cout << "2. Manage Categories\n";
    cout << "3. Manage Products\n";
    cout << "4. Manage Inventory\n";
    cout << "5. View Sales Reports\n";
    cout << "6. View Refund History\n";
    cout << "7. System Settings\n";
    cout << "8. Logout\n";
    cout << "=========================================\n";
}

string Admin::getRoleName() const
{
    return "Admin";
}