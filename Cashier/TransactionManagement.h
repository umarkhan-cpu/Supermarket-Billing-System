#ifndef TRANSACTIONMANAGEMENT_H
#define TRANSACTIONMANAGEMENT_H

#include "Transaction.h"
#include <string>


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
    static void searchByDate(const std::string& date);

    // needed for Refund system
    static bool markAsRefunded(int id);

    // needed for Sales Report
    static int getCount();
    static Transaction getByIndex(int i);

    static void saveToFile();
    static void loadFromFile();

    static void cleanup();
};

#endif