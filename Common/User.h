#ifndef USER_H
#define USER_H

#include <string>
using std::string;

/*
 * User - abstract base class for system users.
 * Belongs to: Muhammad Umar Khan (lead) - hierarchy infrastructure
 *
 * Responsibilities:
 *   - Hold the data common to ALL users (id, username, hash, role, lastLogin)
 *   - Define the interface that all user types must implement
 *
 * Non-responsibilities:
 *   - Does NOT manage authentication (Areesha's UserManagement does that)
 *   - Does NOT manage sessions (SessionManager does that)
 *   - Does NOT prompt the user (subclasses' showDashboard is just a stub
 *     for the polymorphism demo - real menu logic lives in Admin/Cashier
 *     manager classes or the GUI)
 *
 * Design notes:
 *   - This class is ABSTRACT. You cannot instantiate User directly.
 *   - Subclasses (Admin, Cashier) MUST override showDashboard() and
 *     getRoleName(). The compiler enforces this.
 *   - The destructor is virtual so derived classes destruct cleanly when
 *     deleted via a User* pointer.
 *   - Attributes are protected (not private) so subclasses can access
 *     them directly. Public access still goes through getters/setters.
 *
 * CSV format (when stored in Data/users.txt):
 *   userID,username,passwordHash,role,lastLogin
 *   e.g.  1,umar,3947293847,Admin,2026-04-26
 */
class User {
protected:
    int    userID;
    string username;
    string passwordHash;    // Plaintext passwords are a security risk - we store a hash instead.
    string role;            // "Admin" or "Cashier"
    string lastLogin;       // "YYYY-MM-DD" - when this user last logged in

public:
    // ----- Constructors -----
    User();
    User(int id, const string& name, const string& pHash, const string& role);
    User(const User& other);

    // ----- Virtual destructor (REQUIRED for abstract base classes) -----
    // When you `delete user_ptr` and user_ptr is actually pointing at an
    // Admin or Cashier, this ensures the right destructor runs.
    virtual ~User();

    // ----- Getters -----
    int    getID() const;
    string getUsername() const;
    string getPasswordHash() const;
    string getRole() const;
    string getLastLogin() const;

    // ----- Setters (with validation, return bool) -----
    bool setID(int id);
    bool setUsername(const string& u);
    bool setPasswordHash(const string& h);
    bool setLastLogin(const string& date);

    // ----- Pure virtual methods (overridden in child classes) -----
    virtual void   showDashboard() = 0;
    virtual string getRoleName() const = 0;

    // ----- CSV serialization -----
    // toCSV is concrete and shared across all subclasses (uses common fields).
    // No fromCSV here - that lives in UserManagement, which decides whether
    // to construct an Admin or Cashier based on the role field.
    string toCSV() const;
};

#endif