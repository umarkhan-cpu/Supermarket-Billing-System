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

public:
    // Returns today's date as "YYYY-MM-DD" using <ctime>.
    static string todayAsString();

    // ----- File lifecycle -----

    static void loadFromFile();
    static void saveToFile();
    static void cleanup();

    // ----- The main creation method -----

    // Creates a new refund. Validates: txnID exists, within 30-day window,
    // amount within remaining (un-refunded) transaction balance, and now also
    // that the per-product refunded quantity wouldn't exceed what was purchased
    // on the original receipt. After creating the refund, sets the original
    // transaction's status to "Partially Refunded" or "Fully Refunded" based
    // on cumulative refund amount.
    static bool createRefund(int transactionID, const string& reason, float amount,
        int productID, int quantity);

    // ----- Aggregation queries -----

    // Returns the sum of all refund amounts already processed for a given
    // transaction. Used to determine partial vs full status, and to validate
    // that a new refund won't push the cumulative refund over the original total.
    static float getRefundedAmountForTransaction(int txnID);

    // Returns the total quantity of a specific product already refunded
    // against a specific transaction. Used to enforce that you can't refund
    // more units than were purchased. Legacy refund records (without product
    // info) contribute 0 to this count - they're not blocked by this check.
    static int getRefundedQtyForProduct(int txnID, int productID);

    // ----- Read operations -----

    static void viewAll();
    static void viewByTransactionID(int txnID);
    static Refund findByID(int id);
    static int getCount();

    // ----- Console driver -----

    static void showMenu();
};

#endif