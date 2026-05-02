#include "DiscountManagement.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// ============================================================================
// Static member definitions
// ============================================================================

Discount *DiscountManagement::discounts = nullptr;
int DiscountManagement::count = 0;
int DiscountManagement::capacity = 0;

// ============================================================================
// Private helpers
// ============================================================================

void DiscountManagement::grow()
{
    int newCapacity = (capacity == 0) ? 4 : capacity * 2; 
    Discount *newArr = new Discount[newCapacity];

    for (int i = 0; i < count; i++)
    {
        newArr[i] = discounts[i];
    }

    delete[] discounts;
    discounts = newArr;
    capacity = newCapacity;
}

int DiscountManagement::findIndexByID(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (discounts[i].getID() == id)
        {
            return i; // Discount ID found
        }
    }
    return -1; // Discount ID not found
}

int DiscountManagement::findIndexByCode(const string &code)
{
    for (int i = 0; i < count; i++)
    {
        if (discounts[i].getCode() == code)
        {
            return i; // Coupon code found
        }
    }
    return -1; // Coupon code not found
}

int DiscountManagement::nextAvailableID()
{
    int maxId = 0;
    for (int i = 0; i < count; i++)
    {
        if (discounts[i].getID() > maxId)
        {
            maxId = discounts[i].getID();
        }
    }
    return maxId + 1;
}

// ============================================================================
// File lifecycle
// ============================================================================

void DiscountManagement::loadFromFile()
{
    ifstream file("Data/coupons.txt");
    if (!file.is_open())
        return; // file doesn't exist yet — empty collection is fine

    // Clear any previously loaded data so repeated calls don't multiply records.
    delete[] discounts;
    discounts = nullptr;
    count = 0;
    capacity = 0;

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue; // skip blank lines

        Discount d = Discount::fromCSV(line);
        if (d.getID() == 0)
            continue; // skip malformed entries (since ID = 0 indicate incorrect data)

        if (count >= capacity) grow(); // grow the array if no. of discounts exceeds the capacity and add
        discounts[count] = d;
        count++;
    }

    file.close();
}

void DiscountManagement::saveToFile()
{
    ofstream file("Data/coupons.txt");
    if (!file.is_open())
        return;

    for (int i = 0; i < count; i++)
    {
        // Write a discount line (comma separated) into Data/coupons.txt
        file << discounts[i].toCSV() << "\n";
    }

    file.close();
}

void DiscountManagement::cleanup()
{
    delete[] discounts;
    discounts = nullptr;
    count = 0;
    capacity = 0;
}

// ============================================================================
// CRUD operations
// ============================================================================

bool DiscountManagement::addCoupon(const string &code, const string &type, float value)
{
    if (findIndexByCode(code) != -1)
        return false; // Coupon with code already exist

    int newID = nextAvailableID();

    Discount newDisc(newID, code, type, value, true); // new coupons are active by default

    if (newDisc.getCode() == "" || newDisc.getType() == "" || newDisc.getValue() <= 0)
        return false; // if any setter rejected input, we will get default values

    if (count >= capacity)
        grow();
    discounts[count] = newDisc;
    count++;

    saveToFile(); // Append the new discount at the end of Data/coupons.txt

    return true;
}

bool DiscountManagement::editCoupon(int id, const string &newType, float newValue) 
{
    int idx = findIndexByID(id);
    if (idx == -1)
        return false; // ID not found

    // Try the edits on a temporary copy first
    Discount temp = discounts[idx];

    if (!temp.setType(newType))
        return false;
    if (!temp.setValue(newValue))
        return false;

    // Both edits succeeded — commit
    discounts[idx] = temp;
    saveToFile();
    return true;
}

bool DiscountManagement::deleteCoupon(int id)
{
    int idx = findIndexByID(id);
    if (idx == -1)
        return false; // ID not found

    // Shift elements after idx one position left, overwriting discounts[idx]
    for (int i = idx; i < count - 1; i++)
    {
        discounts[i] = discounts[i + 1];
    }

    count--;
    saveToFile();
    return true;
}

bool DiscountManagement::setActive(int id, bool active)
{
    int idx = findIndexByID(id);
    if (idx == -1)
        return false; // ID not found

    // Set the active status of a particular coupon (by Admin)
    discounts[idx].setIsActive(active);

    saveToFile();
    return true;
}

// ============================================================================
// Integration method — called by Billing class
// ============================================================================

float DiscountManagement::applyCoupon(const string &code, float subtotal)
{
    int idx = findIndexByCode(code);
    if (idx == -1)
        return 0; // Coupon code not found

    float discount = discounts[idx].calculateDiscount(subtotal);

    return discount; // calculateDiscount() itself handles the "Inactive" check and returns 0, so we don't need to check separately
}

// ============================================================================
// Read operations
// ============================================================================

/*void DiscountManagement::viewAll()
{
    if (count == 0)
    {
        cout << "\nNo discounts to display.\n";
        return;
    }

    cout << "\n+------+--------------+-------------+---------+----------+\n";
    cout << "| ID   | Code         | Type        | Value   | Status   |\n";
    cout << "+------+--------------+-------------+---------+----------+\n";

    for (int i = 0; i < count; i++)
    {
        cout << "| " << left << setw(5) << discounts[i].getID()
             << "| " << setw(13) << discounts[i].getCode()
             << "| " << setw(12) << discounts[i].getType()
             << "| " << setw(8) << discounts[i].getValue()
             << "| " << setw(9) << (discounts[i].getIsActive() ? "Active" : "Inactive")
             << "|\n";
    }

    cout << "+------+--------------+-------------+---------+----------+\n";
}
*/

Discount DiscountManagement::findByID(int id)
{
    int idx = findIndexByID(id);
    if (idx == -1) return Discount(); // not found — returns default (id=0)
    return discounts[idx]; 
}

int DiscountManagement::getCount()
{
    return count;
}

// ============================================================================
// Console driver (kept as a backup in case GUI fails)
// ============================================================================

/*void DiscountManagement::showMenu()
{
    int choice;

    do
    {
        cout << "\n=== Discount Management ===\n";
        cout << "1. Add Coupon\n";
        cout << "2. Edit Coupon\n";
        cout << "3. Delete Coupon\n";
        cout << "4. Activate/Deactivate Coupon\n";
        cout << "5. Apply Coupon (test)\n";
        cout << "6. View All Coupons\n";
        cout << "7. Back\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string code, type;
            float value;

            cout << "Enter coupon code: ";
            cin >> code;
            cout << "Enter coupon type (PERCENTAGE or FIXED): ";
            cin >> type;
            cout << "Enter coupon value: ";
            cin >> value;

            if (addCoupon(code, type, value))
                cout << "Coupon added successfully.\n";
            else
                cout << "Failed to add coupon. Check for duplicate code or invalid input.\n";
        }
        break;
        case 2:
        {
            int id;
            string newType;
            float newValue;

            cout << "Enter coupon ID to edit: ";
            cin >> id;
            cout << "Enter new coupon type (PERCENTAGE or FIXED): ";
            cin >> newType;
            cout << "Enter new coupon value: ";
            cin >> newValue;

            if (editCoupon(id, newType, newValue))
                cout << "Coupon edited successfully.\n";
            else
                cout << "Failed to edit coupon. Check if ID exists and input is valid.\n";
        }
        break;
        case 3:
        {
            int id;
            cout << "Enter coupon ID to delete: ";
            cin >> id;

            if (deleteCoupon(id))
                cout << "Coupon deleted successfully.\n";
            else
                cout << "Failed to delete coupon. Check if ID exists.\n";
        }
        break;
        case 4:
        {
            int id, activeInt;
            cout << "Enter coupon ID to change status: ";
            cin >> id;
            cout << "Enter new status (0 for Inactive, 1 for Active): ";
            cin >> activeInt;
            bool active = (activeInt == 1);

            if (setActive(id, active))
                cout << "Coupon status updated successfully.\n";
            else
                cout << "Failed to update status. Check if ID exists.\n";
        }
        break;
        case 5:
        {
            string code;
            float subtotal;

            cout << "Enter coupon code to apply: ";
            cin >> code;
            cout << "Enter order subtotal: ";
            cin >> subtotal;

            float discount = applyCoupon(code, subtotal);
            if (discount > 0)
                cout << "Discount applied: " << discount << " Rs.\n";
            else
                cout << "Failed to apply coupon. Check if code exists and is active.\n";
        }
        break;
        case 6:
            viewAll();
            break;
        case 7:
            cout << "Returning to previous menu...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice < 1 || choice > 7);
}
*/