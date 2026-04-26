#ifndef ADMIN_H
#define ADMIN_H

#include "../Common/User.h"
#include <string>
using std::string;

/*
 * Admin - concrete subclass of User.
 * Belongs to: Muhammad Umar Khan (lead) - hierarchy infrastructure
 *
 * Responsibilities:
 *   - Represent a system administrator (one of the two user roles)
 *   - Implement the pure virtual methods inherited from User
 *
 * Non-responsibilities:
 *   - Does NOT manage admin operations (those live in CategoryManagement,
 *     ProductManagement, etc. — admin just identifies the user)
 *   - Does NOT manage authentication or login flow
 *
 * Design notes:
 *   - Admin extends User. By passing "Admin" as the role string in the
 *     constructor, every Admin object is correctly tagged for CSV output
 *     and role-based dispatch.
 *   - showDashboard() is the demonstration of polymorphism — calling
 *     showDashboard() on a User* that points at an Admin runs THIS method,
 *     not Cashier's.
 */
class Admin : public User {
public:
    // ----- Constructors -----
    Admin();
    Admin(int id, const string& uname, const string& pHash);
    Admin(const Admin& other);

    // ----- Override pure virtual methods from User -----
    void   showDashboard() override;
    string getRoleName() const override;
};

#endif