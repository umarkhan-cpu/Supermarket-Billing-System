#ifndef REFUND_H
#define REFUND_H

#include <string>
using std::string;

/*
 * Refund - data class representing a single refund record.
 * Belongs to: Muhammad Umar Khan (lead)
 *
 * Responsibilities:
 *   - Hold the data for ONE refund (id, transactionID, reason, amount, date)
 *   - Know how to serialize itself to/from a CSV line
 *
 * Non-responsibilities:
 *   - Does NOT manage a collection of refunds (that's RefundManagement's job)
 *   - Does NOT validate against the original transaction (that happens in
 *     RefundManagement::createRefund - eventually wires into TransactionManagement)
 *   - Does NOT talk to files directly (only produces/consumes CSV strings)
 *
 * Workflow note:
 *   Refunds are only created when the cashier approves them at the counter.
 *   Rejected attempts are not stored - there's no "REJECTED" status because
 *   the system records what happened, not what didn't.
 *
 * File format (one refund per line in refunds.txt):
 *   refundID,transactionID,reason,amount,date
 *   e.g.  1,42,Damaged item,250,2026-04-25
 *         2,17,Wrong size,1500,2026-04-26
 *
 * Notes:
 *   - reason is the customer's stated reason for the return (free text)
 *   - amount is the refunded amount in rupees (must be > 0)
 *   - date is when the refund was processed (YYYY-MM-DD format)
 *   - reason must not contain commas (CSV safety)
 */
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