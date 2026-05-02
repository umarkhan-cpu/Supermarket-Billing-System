#include "Refund.h"
#include <sstream>
using namespace std;

// ============================================================================
// Constructors
// ============================================================================

Refund::Refund()
    : refundID(0), transactionID(0), reason(""), amount(0), date(""),
      productID(0), quantity(0)
{
}

// Legacy 5-field constructor - kept for backward compatibility with any
// older code path. New refunds should use the 7-field constructor below.
Refund::Refund(int id, int txnID, const string &reason, float amount, const string &date)
    : refundID(0), transactionID(0), reason(""), amount(0), date(""),
      productID(0), quantity(0)
{
    setID(id);
    setTransactionID(txnID);
    setReason(reason);
    setAmount(amount);
    setDate(date);
}

// New 7-field constructor - tracks the specific product and quantity refunded.
Refund::Refund(int id, int txnID, const string &reason, float amount, const string &date,
               int productID, int quantity)
    : refundID(0), transactionID(0), reason(""), amount(0), date(""),
      productID(0), quantity(0)
{
    setID(id);
    setTransactionID(txnID);
    setReason(reason);
    setAmount(amount);
    setDate(date);
    setProductID(productID);
    setQuantity(quantity);
}

Refund::Refund(const Refund &other)
    : refundID(other.refundID),
      transactionID(other.transactionID),
      reason(other.reason),
      amount(other.amount),
      date(other.date),
      productID(other.productID),
      quantity(other.quantity)
{
}

// ============================================================================
// Getters
// ============================================================================

int Refund::getID() const { return refundID; }
int Refund::getTransactionID() const { return transactionID; }
string Refund::getReason() const { return reason; }
float Refund::getAmount() const { return amount; }
string Refund::getDate() const { return date; }
int Refund::getProductID() const { return productID; }
int Refund::getQuantity() const { return quantity; }

// ============================================================================
// Setters
// ============================================================================

bool Refund::setID(int id)
{
    if (id > 0)
    {
        refundID = id;
        return true;
    }
    return false;
}

bool Refund::setTransactionID(int txnID)
{
    if (txnID > 0)
    {
        transactionID = txnID;
        return true;
    }
    return false;
}

bool Refund::setReason(const string &reason)
{
    if (reason != "" && reason.find(',') == reason.npos)
    {
        this->reason = reason;
        return true;
    }
    return false;
}

bool Refund::setAmount(float amount)
{
    if (amount > 0)
    {
        this->amount = amount;
        return true;
    }
    return false;
}

bool Refund::setDate(const string &date)
{
    if (date != "" && date.find(',') == date.npos)
    {
        this->date = date;
        return true;
    }
    return false;
}

bool Refund::setProductID(int productID)
{
    // Allow 0 (legacy records have no product info), but reject negative.
    if (productID >= 0)
    {
        this->productID = productID;
        return true;
    }
    return false;
}

bool Refund::setQuantity(int quantity)
{
    // Same rule - 0 OK for legacy, negative not.
    if (quantity >= 0)
    {
        this->quantity = quantity;
        return true;
    }
    return false;
}

// ============================================================================
// CSV Serialization
// ============================================================================

string Refund::formatFloat(float f)
{
    ostringstream oss;
    oss << f;
    return oss.str();
}

string Refund::toCSV() const
{
    // 7 fields: id, txnID, reason, amount, date, productID, quantity
    return to_string(refundID) + "," + to_string(transactionID) + "," + reason + "," + formatFloat(amount) + "," + date + "," + to_string(productID) + "," + to_string(quantity);
}

Refund Refund::fromCSV(const string &line)
{
    stringstream ss(line);
    string idStr, txnStr, reason, amtStr, date, prodStr, qtyStr;

    getline(ss, idStr, ',');
    getline(ss, txnStr, ',');
    getline(ss, reason, ',');
    getline(ss, amtStr, ',');
    getline(ss, date, ',');

    // Tolerate legacy 5-field format. Any further reads after `date` may
    // hit EOF, in which case prodStr/qtyStr remain empty - we default
    // them to 0 and the refund is treated as having "unknown" product info.
    getline(ss, prodStr, ',');
    getline(ss, qtyStr);

    if (idStr.empty() || txnStr.empty() || reason.empty() || amtStr.empty() || date.empty())
    {
        return Refund();
    }

    try
    {
        int id = stoi(idStr);
        int txnID = stoi(txnStr);
        float amount = stof(amtStr);
        int productID = prodStr.empty() ? 0 : stoi(prodStr);
        int quantity = qtyStr.empty() ? 0 : stoi(qtyStr);

        return Refund(id, txnID, reason, amount, date, productID, quantity);
    }
    catch (const invalid_argument &)
    {
        return Refund();
    }
    catch (const out_of_range &)
    {
        return Refund();
    }
}