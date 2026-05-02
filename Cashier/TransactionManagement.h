#ifndef TRANSACTIONMANAGEMENT_H
#define TRANSACTIONMANAGEMENT_H

#include "Transaction.h"
#include <string>
using std::string;

class TransactionManagement {
private:
    static Transaction* transactions;
    static int count;
    static int capacity;

    // doubles array size when full
    static void resize();

public:
    static void addTransaction(const Transaction& t);

    static void viewHistory();

    static Transaction searchByID(int id);
    static void searchByDate(const string& date);

    // needed for Refund system
    static bool markAsRefunded(int id);

    // Sets the status string of a transaction to any value (e.g. "Partially Refunded",
    // "Fully Refunded"). Used by RefundManagement to set partial vs full status.
    // Saves to file on success.
    static bool setTransactionStatus(int id, const string &status);

    // needed for Sales Report
    static int getCount();

    // Modification by Umar (lead): To add a safeguard for ID generation of transactions
    // Returns max-existing-ID + 1. Used when generating new transaction IDs
    // so that gaps from deletions or wiped-then-reloaded data don't cause
    // duplicate IDs (which would corrupt receipt and refund lookups).
    static int getNextAvailableID();
    static Transaction getByIndex(int i);

    static void saveToFile();
    static void loadFromFile();

    static void cleanup();
};

#endif