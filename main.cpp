#include "Admin/Admin.h"
#include "Cashier/Cashier.h"
#include <iostream>
using namespace std;

int main() 
{
    User* u1 = new Admin(1, "Umar", "abc123");
    User* u2 = new Cashier(2, "Ahmad", "xyz789");
    u1->showDashboard();
    u2->showDashboard();

    return 0;
}