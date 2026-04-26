#ifndef CASHIER_H
#define CASHIER_H

#include "../Common/User.h"
#include <string>
using std::string;

/*
 * Cashier - concrete subclass of User.
 * Belongs to: Muhammad Umar Khan (lead) - hierarchy infrastructure
 *
 * Responsibilities:
 *   - Represent a cashier (the other user role)
 *   - Implement the pure virtual methods inherited from User
 *
 * Non-responsibilities:
 *   - Does NOT handle billing logic (Areesha's Billing class does that)
 *   - Does NOT process refunds (RefundManagement handles that)
 *
 * Design notes:
 *   - Same pattern as Admin: extends User, passes "Cashier" as role.
 *   - showDashboard() and getRoleName() complete the polymorphism contract.
 */
class Cashier : public User {
public:
    // ----- Constructors -----
    Cashier();
    Cashier(int id, const string& uname, const string& pHash);
    Cashier(const Cashier& other);

    // ----- Override pure virtual methods from User -----
    void   showDashboard() override;
    string getRoleName() const override;
};

#endif