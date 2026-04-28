#ifndef ADMIN_H
#define ADMIN_H

#include "../Common/User.h"
#include <string>
using std::string;

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