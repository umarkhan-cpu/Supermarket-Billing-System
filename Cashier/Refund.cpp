#include "Refund.h"
#include <sstream>
using namespace std;

// ============================================================================
// Constructors
// ============================================================================

Refund::Refund() : refundID(0), transactionID(0), reason(""), amount(0), date("") {}

Refund::Refund(int id, int txnID, const string& reason, float amount, const string& date)
    : refundID(0), transactionID(0), reason(""), amount(0), date("")
{
    setID(id);
    setTransactionID(txnID);
    setReason(reason);
    setAmount(amount);
    setDate(date);
}

Refund::Refund(const Refund& other)
    : refundID(other.refundID),
    transactionID(other.transactionID),
    reason(other.reason),
    amount(other.amount),
    date(other.date) {
}

// ============================================================================
// Getters
// ============================================================================

int Refund::getID() const
{
    return refundID;
}

int Refund::getTransactionID() const
{
    return transactionID;
}

string Refund::getReason() const
{
    return reason;
}

float Refund::getAmount() const
{
    return amount;
}

string Refund::getDate() const
{
    return date;
}

// ============================================================================
// Setters
// ============================================================================

bool Refund::setID(int id)
{
    if (id > 0) // ID must be > 0
    {
        refundID = id;
        return true;
    }
    return false;
}

bool Refund::setTransactionID(int txnID)
{
    if (txnID > 0) // Also must be > 0
    {
        transactionID = txnID;
        return true;
    }
    return false;
}

bool Refund::setReason(const string& reason)
{
    // Reason must not be empty or have ','
    if (reason != "" && reason.find(',') == reason.npos)
    {
        this->reason = reason;
        return true;
    }
    return false;
}

bool Refund::setAmount(float amount)
{
    if (amount > 0) // Also must be > 0
    {
        this->amount = amount;
        return true;
    }
    return false;
}

bool Refund::setDate(const string& date)
{
    if (date != "" && date.find(',') == date.npos)
    {
        this->date = date;
        return true;
    }
    return false;
}

// ============================================================================
// CSV Serialization
// ============================================================================

// Formats a float without trailing zeros: 250.0 -> "250", 25.50 -> "25.5"
string Refund::formatFloat(float f)
{
    ostringstream oss;
    oss << f;
    return oss.str();
}

string Refund::toCSV() const
{
    string line = to_string(refundID) + "," + to_string(transactionID) + "," + reason + "," + formatFloat(amount) + "," + date;
    return line;
}

Refund Refund::fromCSV(const string& line)
{
    stringstream ss(line);
    string idStr, txnStr, reason, amtStr, date;

    getline(ss, idStr,  ',');
    getline(ss, txnStr, ',');
    getline(ss, reason, ',');
    getline(ss, amtStr, ',');
    getline(ss, date);

    if (idStr.empty() || txnStr.empty() || reason.empty() || amtStr.empty() || date.empty()) return Refund();

    // Try/catch method to handle invalid_argument or out_of_range value
    // thrown by stoi or stof, in which case a default object is returned
    try
    {
        int id = stoi(idStr);
        int txnID = stoi(txnStr);
        float amount = stof(amtStr);

        return Refund(id, txnID, reason, amount, date);
    }
    catch (const invalid_argument&) { return Refund(); }
    catch (const out_of_range&) { return Refund(); }
}