#ifndef REFUND_H
#define REFUND_H

#include <string>
using std::string;

class Refund {

private:
    int    refundID;
    int    transactionID;   // ties to the original sale (Transaction class)
    string reason;
    float  amount;
    string date;            // "YYYY-MM-DD"

    // Per-product tracking (added so partial refunds can be reconciled
    // against the original receipt's line items without re-parsing receipts).
    int    productID;
    int    quantity;

    // Helper to format a float without trailing zeros (e.g. 250.0 -> "250")
    static string formatFloat(float f);

public:
    // ----- Constructors -----
    Refund();
    Refund(int id, int txnID, const string& reason, float amount, const string& date);
    Refund(int id, int txnID, const string& reason, float amount, const string& date,
        int productID, int quantity);
    Refund(const Refund& other);

    // ----- Getters -----
    int    getID() const;
    int    getTransactionID() const;
    string getReason() const;
    float  getAmount() const;
    string getDate() const;
    int    getProductID() const;
    int    getQuantity() const;

    // ----- Setters (with validation, return bool) -----
    bool setID(int id);
    bool setTransactionID(int txnID);
    bool setReason(const string& reason);
    bool setAmount(float amount);
    bool setDate(const string& date);
    bool setProductID(int productID);
    bool setQuantity(int quantity);

    // ----- CSV Serialization -----
    // New format: id,txnID,reason,amount,date,productID,quantity (7 fields).
    // fromCSV is tolerant of legacy 5-field lines - it defaults productID=0
    // and quantity=0 for those, which won't trip any new validations since
    // they only fire when matching against a specific productID.
    string toCSV() const;
    static Refund fromCSV(const string& line);
};

#endif