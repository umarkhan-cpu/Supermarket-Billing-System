#include "CategoryManagement.h"
#include <iostream>
#include <fstream>
#include <iomanip>     // for table formatting in viewAll() (for console only)
using namespace std;

// ============================================================================
// Static member definitions
// ============================================================================
// Static data members are declared inside the class (in the header) but must
// be defined exactly once in a .cpp file. The array starts as nullptr and is
// allocated on the first call to loadFromFile() or addCategory().

Category* CategoryManagement::categories = nullptr;
int CategoryManagement::count = 0;
int CategoryManagement::capacity = 0;

// ============================================================================
// Private helpers
// ============================================================================

void CategoryManagement::grow() 
{
    int newCapacity = (capacity == 0) ? 4 : capacity * 2;
    Category* newArr = new Category[newCapacity];

    for (int i = 0; i < count; i++) 
    {
        newArr[i] = categories[i];
    }

    delete[] categories;
    categories = newArr;
    capacity = newCapacity;
}

int CategoryManagement::findIndexByID(int id) 
{
    for (int i = 0; i < count; i++) 
    {
        if (categories[i].getID() == id) 
        {
            return i; // Category ID found
        }
    }
    return -1; // Category ID not found
}

int CategoryManagement::nextAvailableID() 
{
    int maxId = 0;
    for (int i = 0; i < count; i++) 
    {
        // check for the max existing ID in the categories array (due to possibility of an unsorted array)
        if (categories[i].getID() > maxId)
        {
            maxId = categories[i].getID();
        }
    }
    return maxId + 1;
}

// ============================================================================
// File lifecycle
// ============================================================================

void CategoryManagement::loadFromFile() 
{
    ifstream file("Data/categories.txt");
    if (!file.is_open()) return;   // file doesn't exist yet - empty collection is fine

    // Clear any previously loaded data so repeated calls don't multiply records.
    delete[] categories;
    categories = nullptr;
    count = 0;
    capacity = 0;

    string line;
    while (getline(file, line)) 
    {
        if (line.empty()) continue;          // skip blank lines

        Category c = Category::fromCSV(line);
        if (c.getID() == 0) continue;        // skip malformed entries (since ID = 0 indicate incorrect data)

        if (count >= capacity) grow();       // grow the array if no. of categories exceeds the capacity and add 
        categories[count] = c;               
        count++;                             
    }

    file.close();
}

void CategoryManagement::saveToFile() 
{
    ofstream file("Data/categories.txt");
    if (!file.is_open()) return;               

    for (int i = 0; i < count; i++) 
    {
        // Write a category line (comma separated) into Data/categories.txt
        file << categories[i].toCSV() << "\n";
    }

    file.close();
}

void CategoryManagement::cleanup() // Static function replacing the destructor (since no instance of CategoryManagement)
{ 
    delete[] categories;
    categories = nullptr;
    count = 0;
    capacity = 0;
}

// ============================================================================
// CRUD(Create, Read, Update, Delete) operations
// ============================================================================

bool CategoryManagement::addCategory(const string& name, const string& desc) 
{
    int newID = nextAvailableID();
    Category newCat(newID, "", "");

    if (!newCat.setName(name) || !newCat.setDescription(desc))  // Return false if input is invalid
        return false;

    if (count >= capacity) grow();       
    categories[count] = newCat;             
    count++;

    saveToFile(); // Append the new category at the end of Data/categories.txt

    return true;
}

bool CategoryManagement::editCategory(int id, const string& newName, const string& newDesc)
{
    int idx = findIndexByID(id);
    if (idx == -1) return false; // ID not found

    // Try the edits on a temporary copy first
    Category temp = categories[idx];

    if (!temp.setName(newName)) return false;
    if (!temp.setDescription(newDesc)) return false;

    // Both edits succeeded - commit
    categories[idx] = temp;
    saveToFile();
    return true;
}

bool CategoryManagement::deleteCategory(int id) 
{
    int idx = findIndexByID(id);
    if (idx == -1) return false; // ID not found

    // Shift elements after idx one position left, overwriting categories[idx]
    for (int i = idx; i < count - 1; i++) 
    {
        categories[i] = categories[i + 1];
    }

    count--;
    saveToFile();
    return true;
}

// ============================================================================
// Read operations
// ============================================================================

void CategoryManagement::viewAll()
{
    if (count == 0) 
    {
        cout << "\nNo categories to display.\n";
        return;
    }

    cout << "\n+------+------------------------+----------------------------------+\n";
    cout << "| ID   | Name                   | Description                      |\n";
    cout << "+------+------------------------+----------------------------------+\n";

    for (int i = 0; i < count; i++) 
    {
        cout << "| " << left << setw(5) << categories[i].getID()
            << "| " << setw(23) << categories[i].getName()
            << "| " << setw(33) << categories[i].getDescription()
            << "|\n";
    }

    cout << "+------+------------------------+----------------------------------+\n";
}

Category CategoryManagement::findByID(int id) 
{
    int idx = findIndexByID(id);
    if (idx == -1) return Category();    // not found - returns default (id=0)
    return categories[idx];             
}

int CategoryManagement::getCount() 
{ 
    return count;
}

// ============================================================================
// Console driver (kept as a backup in case GUI fails)
// ============================================================================

void CategoryManagement::showMenu()
{
    int choice;
    string name, desc;
    int id;

    do 
    {
        cout << "\n=== Category Management ===\n";
        cout << "1. Add Category\n";
        cout << "2. Edit Category\n";
        cout << "3. Delete Category\n";
        cout << "4. View All\n";
        cout << "5. Back\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) 
        {
        case 1:
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter description: ";
            getline(cin, desc);
            if (addCategory(name, desc))
                cout << "Category added.\n";
            else
                cout << "Invalid input. Category not added.\n";
            break;

        case 2:
            cout << "Enter ID to edit: ";
            cin >> id;
            cin.ignore();
            cout << "New name: ";
            getline(cin, name);
            cout << "New description: ";
            getline(cin, desc);
            if (editCategory(id, name, desc))
                cout << "Category updated.\n";
            else
                cout << "Edit failed (invalid ID or input).\n";
            break;

        case 3:
            cout << "Enter ID to delete: ";
            cin >> id;
            cin.ignore();
            if (deleteCategory(id))
                cout << "Category deleted.\n";
            else
                cout << "ID not found.\n";
            break;

        case 4:
            viewAll();
            break;

        case 5:
            cout << "Returning...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}