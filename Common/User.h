#ifndef USER_H
#define USER_H

#include <string>
using std::string;

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