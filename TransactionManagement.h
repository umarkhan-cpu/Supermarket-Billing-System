#ifndef TRANSACTIONMANAGEMENT_H
#define TRANSACTIONMANAGEMENT_H

#include "Transaction.h"
#include <string>


//class for transaction management 
class TransactionManagement {
private:

    // dynamic array for transactions
    static Transaction* transactions;
    static int count;
    static int capacity;

    // resize function for ease  
    static void resize();

public:

    // add transaction
    static void addTransaction(const Transaction& t);

    // view 
    static void viewHistory();

    // search 
    static Transaction searchByID(int id);
    static void searchByDate(const std::string& date);

    // save and load 
    static void saveToFile();
    static void loadFromFile();
};

#endif