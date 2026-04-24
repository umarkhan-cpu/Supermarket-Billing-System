#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Transaction {
private:
    string date;
    int receiptID;
    double totalAmount;

public:
    Transaction(string d = "", int id = 0, double amt = 0.0)
        : date(d), receiptID(id), totalAmount(amt) {
    }

    double getAmount() const { return totalAmount; }
    string getDate() const { return date; }

    bool readFromFile(ifstream& file) {
        if (file >> date >> receiptID >> totalAmount) {
            return true;
        }
        return false;
    }

    void display() const {
        cout << date << "\t" << receiptID << "\t\t$" << totalAmount << endl;
    }
};

class BillingSystem {
private:
    string filename;

public:
    BillingSystem(string f) : filename(f) {}

    void processSale(string date, int receiptID, double amount) {
        // ios::app ensures it creates the file if it doesn't exist and adds t the bottom
        ofstream file(filename, ios::app);

        if (file.is_open()) {
            // Write data separated by spaces, then go to the next line (\n)
            file << date << " " << receiptID << " " << amount << "\n";
            file.close();
            cout << "[Success] Sale saved to file! (Receipt: " << receiptID << ")" << endl;
        }
        else {
            cout << "[Error] Could not open file to save sale." << endl;
        }
    }
};

class ReportGenerator {
private:
    string filename;

public:
    ReportGenerator(string f) : filename(f) {}

    void generateTotalSalesReport() {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "No sales data found. (File doesn't exist yet!)" << endl;
            return;
        }

        Transaction temp; 
        double totalRevenue = 0.0;
        int totalTransactions = 0;

        cout << "\n=======================================" << endl;
        cout << "          TOTAL SALES REPORT           " << endl;
        cout << "=======================================" << endl;
        cout << "Date\t\tReceipt ID\tAmount" << endl;
        cout << "---------------------------------------" << endl;

        while (temp.readFromFile(file)) {
            temp.display();
            totalRevenue += temp.getAmount();
            totalTransactions++;
        }

        file.close();

        cout << "---------------------------------------" << endl;
        cout << "Total Transactions: " << totalTransactions << endl;
        cout << "Total Revenue: " << totalRevenue << endl;
        cout << "=======================================\n" << endl;
    }
};
int main() {
    string myFile = "transactions.txt";

    BillingSystem cashier(myFile);
    ReportGenerator admin(myFile);

    cout << "--- SUPERMARKET BILLING SYSTEM ---\n" << endl;

    cashier.processSale("2026-04-24", 1001, 45.50);
    cashier.processSale("2026-04-24", 1002, 120.75);
    cashier.processSale("2026-04-25", 1003, 15.00);

    admin.generateTotalSalesReport();

    return 0;
}

