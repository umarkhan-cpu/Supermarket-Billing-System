#ifndef REFUND_MANAGEMENT_H
#define REFUND_MANAGEMENT_H

#include "Refund.h"
#include <string>
using std::string;

/*
 * RefundManagement - static manager class for the Refund collection.
 * Belongs to: Muhammad Umar Khan (lead)
 *
 * Responsibilities:
 *   - Owns the in-memory dynamic array of all loaded Refund objects
 *   - Handles persistence (load/save) against Data/refunds.txt
 *   - Exposes createRefund() - the cashier's main action at the counter
 *   - Provides read-only methods for admin auditing
 *   - Provides a console menu (showMenu) for interactive use
 *
 * Design notes:
 *   - All members are static. There is only one conceptual "refund system"
 *     in the application, so no instances are created.
 *   - createRefund returns false on validation failure WITHOUT creating a
 *     record. Rejected refund attempts are not logged - they only exist as
 *     verbal interactions at the counter.
 *   - There is no editRefund or deleteRefund. Refunds are an audit trail.
 *     Once recorded, they are immutable.
 *   - INTEGRATION POINTS (TODO when Farda ships her classes):
 *       1. Validate transactionID against TransactionManagement
 *       2. Validate that the transaction date is within 30 days of today
 *       3. Update inventory: add back the refunded products to stock
 *
 * File path: Data/refunds.txt (relative to the project root)
 */
class RefundManagement {

private:
    static Refund* refunds;
    static int count;
    static int capacity;

    // ----- Private helpers -----

    static void grow();
    static int findIndexByID(int id);
    static int nextAvailableID();

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
    //
    // Returns true on successful creation, false otherwise.
    //
    // TODO (when Farda's classes ship):
    //   - Look up the transaction in TransactionManagement, reject if missing
    //   - Compare transaction date to today, reject if older than 30 days
    //   - Call InventoryManagement::addStock(productID, qty) for each refunded item
    static bool createRefund(int transactionID, const string& reason, float amount);

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