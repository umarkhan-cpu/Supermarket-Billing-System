#pragma once
#include <string>
#include <fstream>
using namespace std;

class Transaction {
private:
    string date;
    int receiptID;
    double totalAmount;

public:
    Transaction(string d = "", int id = 0, double amt = 0.0);

    double getAmount() const;
    string getDate() const;

    bool readFromFile(ifstream& file);
    void display() const;
};
class BillingSystem {
private:
    string filename;

public:
    BillingSystem(string f);
    void processSale(string date, int receiptID, double amount);
};

class ReportGenerator {
private:
    string filename;

public:
    ReportGenerator(string f);
    void generateTotalSalesReport();
};
