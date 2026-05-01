#include "RefundManagement.h"
#include "Transaction.h"
#include "TransactionManagement.h"
#include "../Admin/Product.h"
#include "../Admin/ProductManagement.h"
#include "../Admin/InventoryManagement.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;

static struct tm parseDate(const string& dateStr) 
{
    struct tm date = {};
    char dash;
    stringstream ss(dateStr);
    int year, month, day;
    ss >> year >> dash >> month >> dash >> day;
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;
    return date;
}

// ============================================================================
// Static member definitions
// ============================================================================

Refund* RefundManagement::refunds = nullptr;
int RefundManagement::count = 0;
int RefundManagement::capacity = 0;

// ============================================================================
// Private helpers
// ============================================================================

void RefundManagement::grow()
{
    int newCapacity = (capacity == 0) ? 4 : capacity * 2;
    Refund* newArr = new Refund[newCapacity];

    for (int i = 0; i < count; i++)
    {
        newArr[i] = refunds[i];
    }

    delete[] refunds;
    refunds = newArr;
    capacity = newCapacity;
}

int RefundManagement::findIndexByID(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (refunds[i].getID() == id)
        {
            return i; // Refund ID found
        }
    }
    return -1; // Refund ID not found
}

int RefundManagement::nextAvailableID()
{
    int maxId = 0;
    for (int i = 0; i < count; i++)
    {
        if (refunds[i].getID() > maxId)
        {
            maxId = refunds[i].getID();
        }
    }
    return maxId + 1;
}

// Returns today's date as "YYYY-MM-DD" using <ctime>.
// Used as the date stamp when a refund is created.
string RefundManagement::todayAsString()
{
    time_t now = time(nullptr);
    tm local;
    localtime_s(&local, &now);   // Windows-safe variant of localtime

    stringstream ss;
    ss << (local.tm_year + 1900) << "-"
        << setw(2) << setfill('0') << (local.tm_mon + 1) << "-"
        << setw(2) << setfill('0') << local.tm_mday;
    return ss.str();
}

int RefundManagement::daysBetween(const string& tr_Date, const string& today)
{
    struct tm trDate = parseDate(tr_Date);
    struct tm todayDate = parseDate(today);
    time_t trTime = mktime(&trDate);
    time_t todayTime = mktime(&todayDate);
    return (int)(difftime(todayTime, trTime) / 86400);
}

// ============================================================================
// File lifecycle
// ============================================================================

void RefundManagement::loadFromFile()
{
    ifstream file(R"(C:\Users\mahno\OneDrive\Documents\GitHub\Supermarket-Billing-System\Data\refunds.txt)");
    if (!file.is_open())
        return; // file doesn't exist yet — empty collection is fine

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue; // skip blank lines

        Refund r = Refund::fromCSV(line);
        if (r.getID() == 0)
            continue; // skip malformed entries (since ID = 0 indicate incorrect data)

        if (count >= capacity) grow(); // grow the array if no. of refunds exceeds the capacity and add
        refunds[count] = r;
        count++;
    }

    file.close();
}

void RefundManagement::saveToFile()
{
    ofstream file(R"(C:\Users\mahno\OneDrive\Documents\GitHub\Supermarket-Billing-System\Data\refunds.txt)");
    if (!file.is_open())
        return;

    for (int i = 0; i < count; i++)
    {
        // Write a refund line (comma separated) into Data/coupons.txt
        file << refunds[i].toCSV() << "\n";
    }

    file.close();
}

void RefundManagement::cleanup()
{
     delete[] refunds;
     refunds = nullptr; 
     count = 0;
     capacity = 0;
}

// ============================================================================
// The main creation method
// ============================================================================
bool RefundManagement::createRefund(int transactionID, const string& reason, float amount,
    int productID, int quantity)
{
    // Input validation
    if (transactionID <= 0) return false;
    if (reason == "")       return false;
    if (amount <= 0)        return false;
    if (productID <= 0)     return false;
    if (quantity <= 0)      return false;

    // Validate transaction exists
    Transaction t = TransactionManagement::searchByID(transactionID);
    if (t.getID() == 0) return false;

    // 30-day refund window check
    string today = todayAsString();
    int daysDiff = daysBetween(t.getDate(), today);
    if (daysDiff > 30) return false;     // too old
    if (daysDiff < 0)  return false;     // corrupt data

    // Refund amount cannot exceed original transaction total
    if (amount > t.getTotalAmount()) return false;

    // Validate that the product being returned actually exists
    Product p = ProductManagement::findByID(productID);
    if (p.getID() == 0) return false;    // product doesn't exist

    // All validations passed — create and store the refund
    int newID = nextAvailableID();
    Refund newRef(newID, transactionID, reason, amount, today);

    if (count >= capacity) grow();
    refunds[count] = newRef;
    count++;

    saveToFile();

    // Restock the returned product back into inventory
    InventoryManagement::addStock(productID, quantity);

    // Mark the original transaction as refunded
    TransactionManagement::markAsRefunded(transactionID);

    return true;
}

// ============================================================================
// Read operations
// ============================================================================

/*void RefundManagement::viewAll()
{
    if (count == 0) 
    {
        cout << "\nNo refunds to display.\n";
        return;
    }

    cout << "\n+------+----------+--------------------------+----------+------------+\n";
    cout << "| ID   | Txn ID   | Reason                   | Amount   | Date       |\n";
    cout << "+------+----------+--------------------------+----------+------------+\n";

    for (int i = 0; i < count; i++) 
    {
        cout << "| " << left << setw(5) << refunds[i].getID()
            << "| " << setw(9) << refunds[i].getTransactionID()
            << "| " << setw(25) << refunds[i].getReason()
            << "| " << setw(9) << refunds[i].getAmount()
            << "| " << setw(11) << refunds[i].getDate()
            << "|\n";
    }

    cout << "+------+----------+--------------------------+----------+------------+\n";
}
*/

void RefundManagement::viewByTransactionID(int txnID)
{
    bool found = false;

    for (int i = 0; i < count; i++) 
    {
        if (refunds[i].getTransactionID() == txnID) 
        {
            if (!found) 
            {
                // Print header only once, on the first match
                cout << "\n+------+----------+--------------------------+----------+------------+\n";
                cout << "| ID   | Txn ID   | Reason                   | Amount   | Date       |\n";
                cout << "+------+----------+--------------------------+----------+------------+\n";
            }
            cout << "| " << left << setw(5) << refunds[i].getID()
                << "| " << setw(9) << refunds[i].getTransactionID()
                << "| " << setw(25) << refunds[i].getReason()
                << "| " << setw(9) << refunds[i].getAmount()
                << "| " << setw(11) << refunds[i].getDate()
                << "|\n";
            found = true;
        }
    }

    if (found)
        cout << "+------+----------+--------------------------+----------+------------+\n";
    else
        cout << "No refunds for transaction " << txnID << "\n";
}

Refund RefundManagement::findByID(int id)
{
    int idx = findIndexByID(id);
    if (idx == -1) return Refund(); // not found — returns default (id=0)
    return refunds[idx];
}

int RefundManagement::getCount()
{
    return count;
}

// ============================================================================
// Console driver (kept as a backup in case GUI fails)
// ============================================================================

/*void RefundManagement::showMenu()
{
    int choice;

    do
    {
        cout << "\n=== Refund Management ===\n";
        cout << "1. Process Refund\n";
        cout << "2. View All Refunds\n";
        cout << "3. Find Refund by ID\n";
        cout << "4. View Refunds by Transaction ID\n";
        cout << "5. Back\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            int txnID, productID, quantity;
            string reason;
            float amount;

            cout << "Enter transaction ID: ";
            cin >> txnID;
            cin.ignore();
            cout << "Enter reason for refund: ";
            getline(cin, reason);
            cout << "Enter refund amount (Rs.): ";
            cin >> amount;
            cout << "Enter product ID being returned: ";
            cin >> productID;
            cout << "Enter quantity returned: ";
            cin >> quantity;
            cin.ignore();

            if (createRefund(txnID, reason, amount, productID, quantity))
                cout << "Refund processed successfully. Inventory restocked.\n";
            else
                cout << "Failed to process refund. Check inputs.\n";
        }
        break;
        break;
        case 2:
            viewAll();
            break;
        case 3:
        {
            int id;
            cout << "Enter refund ID: ";
            cin >> id;
            cin.ignore();

            Refund r = findByID(id);
            if (r.getID() == 0)
            {
                cout << "Refund not found.\n";
            }
            else
            {
                cout << "\nRefund Details:\n";
                cout << "  ID:              " << r.getID() << "\n";
                cout << "  Transaction ID:  " << r.getTransactionID() << "\n";
                cout << "  Reason:          " << r.getReason() << "\n";
                cout << "  Amount:          Rs. " << r.getAmount() << "\n";
                cout << "  Date:            " << r.getDate() << "\n";
            }
        }
        break;
        case 4:
        {
            int txnID;
            cout << "Enter transaction ID: ";
            cin >> txnID;
            cin.ignore();
            viewByTransactionID(txnID);
        }
        break;
        case 5:
            cout << "Returning to previous menu...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}
*/