#ifndef CASHIER_H
#define CASHIER_H

#include "../Common/User.h"
#include <string>
using std::string;

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