#include "FilterAndSearch.h"
#include <iostream>
using namespace std;

int main() {
    // Step 1: Create Record object
    Record r;

    // Step 2: Load data from files
    r.loadCategories();
    r.loadProducts();

    // Step 3: Create SearchFilter object
    SearchFilter sf(&r);

    int choice;

    do {
        cout << "\n====== MENU ======\n";
        cout << "1. Show All Products\n";
        cout << "2. Search by Name\n";
        cout << "3. Filter by Category ID\n";
        cout << "4. Filter by Price Range\n";
        cout << "5. Show In-Stock Products\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            sf.showAll();
        }
        else if (choice == 2) {
            string name;
            cout << "Enter name to search: ";
            cin >> name;
            sf.searchByName(name);
        }
        else if (choice == 3) {
            int id;
            cout << "Enter category ID: ";
            cin >> id;
            sf.filterByCategory(id);
        }
        else if (choice == 4) {
            float min, max;
            cout << "Enter min price: ";
            cin >> min;
            cout << "Enter max price: ";
            cin >> max;
            sf.filterByPrice(min, max);
        }
        else if (choice == 5) {
            sf.inStock();
        }

    } while (choice != 0);

    cout << "Exiting program...\n";
    return 0;
}