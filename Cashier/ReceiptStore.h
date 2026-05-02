#ifndef RECEIPT_STORE_H
#define RECEIPT_STORE_H

#include <string>
using std::string;

// A line item within a receipt - one row per product purchased.
// Stored values are immutable - they reflect what was paid at the time
// of sale, so refunds can be processed against the original price even
// if product prices change later.
struct ReceiptItem {
    int    productID;
    string productName;
    int    quantity;
    float  unitPrice;     // price at time of sale
    float  lineTotal;     // unitPrice * quantity

    ReceiptItem();
    ReceiptItem(int pid, const string& name, int qty, float unit);
};

// A full receipt: header info, all line items, and totals.
// Created once on Checkout, never modified afterwards.
class ReceiptRecord {
public:
    int    transactionID;
    string dateTime;       // human-readable date/time
    string cashierName;
    string type;           // "Sale" or "Refund"

    static const int MAX_ITEMS = 100;
    ReceiptItem items[MAX_ITEMS];
    int    itemCount;

    float  subtotal;
    float  discount;
    float  tax;
    float  grandTotal;

    ReceiptRecord();

    // Adds an item. Returns false if MAX_ITEMS reached.
    bool addItem(const ReceiptItem& item);

    // Helpful for the refund flow: find a specific line item by product ID.
    // Returns -1 if not found.
    int findItemByProductID(int productID) const;
};

// Persistence layer. Loads/saves all receipts to Data/receipts.txt.
// File format (pipe-delimited so commas in names don't break parsing).
// Multiple receipts in one file, separated by =RECEIPT= markers.
class ReceiptStore {
public:
    // Append a receipt to the file. Used after Checkout (sale) and after
    // refund processing.
    static bool saveReceipt(const ReceiptRecord& receipt);

    // Look up a receipt by transaction ID. Returns a default-constructed
    // ReceiptRecord (transactionID == 0) if not found.
    // For a transaction with both a sale receipt AND a refund receipt,
    // this returns the FIRST match - which will be the original sale,
    // since sales are written before refunds.
    static ReceiptRecord findByTransactionID(int transactionID);

    // Like findByTransactionID but specifically asks for the sale receipt
    // (skips refund receipts with the same txnID). Used by RefundForm to
    // ensure it pulls the original sale, never a previous refund record.
    static ReceiptRecord findSaleByTransactionID(int transactionID);
};

#endif