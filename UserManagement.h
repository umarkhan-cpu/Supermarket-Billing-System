#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cstdlib>

using namespace std;

class UserManagement {
private:
    string username, password;
    int num1, num2, ans;
    char op;

    string passtrength(string password);
    bool userverify(string fuser, string fpass);
    bool userexists(string fuser);
    void generatecaptcha();
    bool validatecaptcha();

public:
    UserManagement();
    static string hashedpass(string pass);
    void signup(string role);
    bool login();
    void deleteAccount();
    void menu();
};

#endif