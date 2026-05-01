#include "FilterAndSearch.h"
#include <iostream>
#include <string>
using namespace std;

// Prints a single product row using the category name resolved from CategoryManagement.  
static void printProduct(const Product& p) {
    string cName = CategoryManagement::findByID(p.getCategoryID()).getName();// Get cname using cID of the product
    p.display(/*cName*/);
}


void SearchFilter::showAll() {
    cout << "All Products:" << endl;
    for (int i = 0; i < ProductManagement::getCount(); i++) {
        printProduct(ProductManagement::getAt(i));
    }
}

void SearchFilter::searchByName(const string& name) {
    cout << "Search Results:" << endl;
    for (int i = 0; i < ProductManagement::getCount(); i++) {
        Product p = ProductManagement::getAt(i);
        if (p.getName().find(name) != string::npos) {
            printProduct(p);
        }
    }
}

void SearchFilter::filterByCategory(int categoryID) {
    cout << "Products in Category " << categoryID << ":" << endl;
    for (int i = 0; i < ProductManagement::getCount(); i++) {
        Product p = ProductManagement::getAt(i); //getAt finds product stored at index i
        if (p.getCategoryID() == categoryID) {   
            printProduct(p);
        }
    }
}

void SearchFilter::filterByPrice(float min, float max) {
    cout << "Products between " << min << " and " << max << ":" << endl;
    for (int i = 0; i < ProductManagement::getCount(); i++) {
        Product p = ProductManagement::getAt(i);
        if (p.getPrice() >= min && p.getPrice() <= max) {
            printProduct(p);
        }
    }
}

void SearchFilter::inStock() {
    cout << "In-Stock Products:" << endl;
    for (int i = 0; i < ProductManagement::getCount(); i++) {
        Product p = ProductManagement::getAt(i);
        if (p.getStock() > 0) {
            printProduct(p);
        }
    }
}

void SearchFilter::menu() {
    int choice;

    do {
        cout << "~~SEARCH & FILTER MENU~~" << endl;
        cout << "1. Show All Products" << endl;
        cout << "2. Search by Name" << endl;
        cout << "3. Filter by Category" << endl;
        cout << "4. Filter by Price Range" << endl;
        cout << "5. Show In-Stock Products" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            showAll();
            break;

        case 2: {
            string name;
            cout << "Enter product name: ";
            cin >> name;
            searchByName(name);
            break;
        }

        case 3: {
            int catId;
            cout << "Enter category ID: ";
            cin >> catId;
            filterByCategory(catId);
            break;
        }

        case 4: {
            float min, max;
            cout << "Enter min price: ";
            cin >> min;
            cout << "Enter max price: ";
            cin >> max;
            filterByPrice(min, max);
            break;
        }

        case 5:
            inStock();
            break;

        case 6:
            cout << "Exiting Search Menu..." << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 6);
}