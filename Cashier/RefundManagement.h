#ifndef REFUND_MANAGEMENT_H
#define REFUND_MANAGEMENT_H

#include "Refund.h"
#include <string>
using std::string;

class RefundManagement {

private:
    static Refund* refunds;
    static int count;
    static int capacity;

    // ----- Private helpers -----

    static void grow();
    static int findIndexByID(int id);
    static int nextAvailableID();
    static int daysBetween(const string& t_Date, const string& today);

    // Returns today's date as "YYYY-MM-DD" using <ctime>.
    // Used as the date stamp when a refund is created.
    static string todayAsString();

public:
    // ----- File lifecycle -----

    static void loadFromFile();
    static void saveToFile();
    static void cleanup();

    // ----- The main creation method -----

    // Creates a new refund record for a given transaction.
    // The cashier calls this after verifying receipt + return window verbally.
    // The refund ID and date are auto-assigned. Returns false if any input
    // fails validation; in that case no record is created.
    // Returns true on successful creation, false otherwise.
    static bool createRefund(int transactionID, const string& reason, float amount,
                             int productID, int quantity);

    // ----- Read operations -----

    static void viewAll();

    // Lists all refunds linked to a specific transaction ID.
    // Useful for admins auditing "has this transaction been refunded?"
    static void viewByTransactionID(int txnID);

    static Refund findByID(int id);
    static int getCount();

    // ----- Console driver -----

    static void showMenu();
};

#endif