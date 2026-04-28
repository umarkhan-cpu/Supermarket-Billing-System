#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <fstream>

class Transaction {
private:
    int TransactionID;
    std::string date;
    int CashierID;
    float TotalAmount;
    std::string status;

public:
    Transaction();

    // Set full transaction
    void setData(int TID, std::string D, int CID, float amount, std::string st);

    // (status update after creation
    void setStatus(const std::string& st);

    // Getters
    int getID() const;
    std::string getDate() const;
    int getCashierID() const;
    float getTotalAmount() const;
    std::string getStatus() const;

    // Display transaction on screen
    void show() const;

    // Save / Load in CSV format
    void save(std::ofstream& out);
    bool load(std::ifstream& in);
};

#endif