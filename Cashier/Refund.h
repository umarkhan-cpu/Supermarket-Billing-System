#ifndef REFUND_H
#define REFUND_H

#include <string>
using std::string;

class Refund {

private:
    int    refundID;
    int    transactionID;   // ties to the original sale (Farda's Transaction class)
    string reason;
    float  amount;
    string date;            // "YYYY-MM-DD"

    // Helper to format a float without trailing zeros (e.g. 250.0 -> "250")
    static string formatFloat(float f);

public:
    // ----- Constructors -----
    Refund();
    Refund(int id, int txnID, const string& reason, float amount, const string& date);
    Refund(const Refund& other);

    // ----- Getters -----
    int    getID() const;
    int    getTransactionID() const;
    string getReason() const;
    float  getAmount() const;
    string getDate() const;

    // ----- Setters (with validation, return bool) -----
    // Validation rules:
    //   - ID must be positive (> 0)
    //   - Transaction ID must be positive (> 0)
    //   - Reason must be non-empty and must not contain commas (CSV safety)
    //   - Amount must be > 0
    //   - Date must be non-empty (format check is light - caller should pass YYYY-MM-DD)
    bool setID(int id);
    bool setTransactionID(int txnID);
    bool setReason(const string& reason);
    bool setAmount(float amount);
    bool setDate(const string& date);

    // ----- CSV Serialization -----
    string toCSV() const;
    static Refund fromCSV(const string& line);
};

#endif