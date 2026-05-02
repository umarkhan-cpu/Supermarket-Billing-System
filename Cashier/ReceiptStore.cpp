#include "ReceiptStore.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// ---------- ReceiptItem ----------

ReceiptItem::ReceiptItem()
    : productID(0), productName(""), quantity(0), unitPrice(0.0f), lineTotal(0.0f) {
}

ReceiptItem::ReceiptItem(int pid, const string& name, int qty, float unit)
    : productID(pid), productName(name), quantity(qty), unitPrice(unit) {
    lineTotal = unit * qty;
}

// ---------- ReceiptRecord ----------

ReceiptRecord::ReceiptRecord()
    : transactionID(0), dateTime(""), cashierName(""), type(""),
    itemCount(0), subtotal(0.0f), discount(0.0f), tax(0.0f), grandTotal(0.0f) {
}

bool ReceiptRecord::addItem(const ReceiptItem& item) {
    if (itemCount >= MAX_ITEMS) return false;
    items[itemCount++] = item;
    return true;
}

int ReceiptRecord::findItemByProductID(int productID) const {
    for (int i = 0; i < itemCount; i++) {
        if (items[i].productID == productID) return i;
    }
    return -1;
}

// ---------- ReceiptStore ----------

// Helper: split a pipe-delimited line into tokens.
// We use a fixed-size out array since this is a closed format.
static int splitPipes(const string& line, string out[], int maxFields) {
    int count = 0;
    string current;
    for (size_t i = 0; i < line.size() && count < maxFields; i++) {
        if (line[i] == '|') {
            out[count++] = current;
            current = "";
        }
        else {
            current += line[i];
        }
    }
    if (count < maxFields) {
        out[count++] = current;
    }
    return count;
}

bool ReceiptStore::saveReceipt(const ReceiptRecord& receipt) {
    // Append mode - we're adding to a multi-receipt file, never overwriting.
    ofstream out("Data/receipts.txt", ios::app);
    if (!out) return false;

    out << "=RECEIPT=\n";
    out << "HEADER|" << receipt.transactionID << "|" << receipt.dateTime
        << "|" << receipt.cashierName << "|" << receipt.type << "\n";

    for (int i = 0; i < receipt.itemCount; i++) {
        const ReceiptItem& it = receipt.items[i];
        out << "ITEM|" << it.productID << "|" << it.productName << "|"
            << it.quantity << "|" << it.unitPrice << "|" << it.lineTotal << "\n";
    }

    out << "TOTALS|" << receipt.subtotal << "|" << receipt.discount
        << "|" << receipt.tax << "|" << receipt.grandTotal << "\n";
    out << "END\n";

    out.close();
    return true;
}

// Internal: scan the file, return the first receipt matching the given
// transactionID. If matchSaleOnly is true, skip records with type == "Refund".
static ReceiptRecord findInternal(int transactionID, bool matchSaleOnly) {
    ReceiptRecord empty;  // will be returned if not found

    ifstream in("Data/receipts.txt");
    if (!in.is_open()) return empty;

    ReceiptRecord current;
    bool inReceipt = false;
    string line;

    while (getline(in, line)) {
        if (line == "=RECEIPT=") {
            // Start of a new receipt - reset accumulator
            current = ReceiptRecord();
            inReceipt = true;
            continue;
        }

        if (!inReceipt) continue;

        if (line == "END") {
            // Receipt complete. Check if this is the one we want.
            if (current.transactionID == transactionID) {
                if (!matchSaleOnly || current.type == "Sale") {
                    return current;
                }
            }
            inReceipt = false;
            continue;
        }

        // Otherwise it's a HEADER, ITEM, or TOTALS line - parse it
        string fields[6];
        int fieldCount = splitPipes(line, fields, 6);
        if (fieldCount == 0) continue;

        if (fields[0] == "HEADER" && fieldCount >= 5) {
            try {
                current.transactionID = std::stoi(fields[1]);
            }
            catch (...) { current.transactionID = 0; }
            current.dateTime = fields[2];
            current.cashierName = fields[3];
            current.type = fields[4];
        }
        else if (fields[0] == "ITEM" && fieldCount >= 6) {
            ReceiptItem item;
            try {
                item.productID = stoi(fields[1]);
                item.productName = fields[2];
                item.quantity = stoi(fields[3]);
                item.unitPrice = stof(fields[4]);
                item.lineTotal = stof(fields[5]);
                current.addItem(item);
            }
            catch (...) {
                // skip malformed item
            }
        }
        else if (fields[0] == "TOTALS" && fieldCount >= 5) {
            try {
                current.subtotal = stof(fields[1]);
                current.discount = stof(fields[2]);
                current.tax = stof(fields[3]);
                current.grandTotal = stof(fields[4]);
            }
            catch (...) {
                // leave totals at 0
            }
        }
    }

    in.close();
    return empty;  // not found
}

ReceiptRecord ReceiptStore::findByTransactionID(int transactionID) {
    return findInternal(transactionID, false);
}

ReceiptRecord ReceiptStore::findSaleByTransactionID(int transactionID) {
    return findInternal(transactionID, true);
}