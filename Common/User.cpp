#include "User.h"
using namespace std;

// ============================================================================
// Constructors
// ============================================================================

User::User() : userID(0), username(""), passwordHash(""), role(""), lastLogin("") {}

User::User(int id, const string& uname, const string& pHash, const string& r) : userID(0), username(""), 
                                                                                passwordHash(""), role(""), lastLogin("")
{
    // Use setters for validation
    setID(id);
    setUsername(uname);
    setPasswordHash(pHash);
    role = r; // We don't validate role here - Admin and Cashier subclass
              // constructors will pass exactly "Admin" or "Cashier" themselves

    // lastLogin stays at "" - gets set later when the user actually logs in
}

User::User(const User& other)
    : userID(other.userID),
    username(other.username),
    passwordHash(other.passwordHash),
    role(other.role),
    lastLogin(other.lastLogin) {
}

// Virtual destructor - body is empty, but its presence ensures derived
// class destructors run when deleting via a User* pointer.
User::~User() {}

// ============================================================================
// Getters
// ============================================================================

int User::getID() const
{
    return userID;
}

string User::getUsername() const
{
    return username;
}

string User::getPasswordHash() const
{
    return passwordHash;
}

string User::getRole() const
{
    return role;
}

string User::getLastLogin() const
{
    return lastLogin;
}

// ============================================================================
// Setters
// ============================================================================

bool User::setID(int id)
{
    if (id > 0) // ID must be > 0
    {
        userID = id;
        return true;
    }
    return false;
}

bool User::setUsername(const string& u)
{
    // username must not be empty or have ',' or ' '
    if (u != "" && u.find(',') == u.npos && u.find(' ') == u.npos)
    {
        username = u;
        return true;
    }
    return false;
}

bool User::setPasswordHash(const string& h)
{
    if (h != "" && h.find(',') == h.npos)
    {
        passwordHash = h;
        return true;
    }
    return false;
}

bool User::setLastLogin(const string& date)
{
    if (date.find(',') == date.npos) // Can be empty - first time logging in
    {
        lastLogin = date;
        return true;
    }
    return false;
}

// ============================================================================
// CSV serialization
// ============================================================================

string User::toCSV() const
{
    string line = to_string(userID) + "," + username + "," + passwordHash + "," + role + "," + lastLogin;
    return line;
}

// Note: no User::fromCSV - UserManagement handles parsing because it
// needs to decide whether to construct an Admin or Cashier based on
// the role field.