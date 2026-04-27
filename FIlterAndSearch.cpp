#include "FilterAndSearch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Record::Record(int maxP, int maxC) {
    maxProducts = maxP;
    maxCategories = maxC;
    products = new Product[maxProducts];
    categories = new Category[maxCategories];
    productCount = 0;
    categoryCount = 0;
}

Record::~Record() {
    delete[] products;
    delete[] categories;
}

void Record::loadCategories() {
    string line;
    ifstream file("categories.txt");

    if (!file) {
        cout << "Error opening category file" << endl;
        return;
    }

    getline(file, line);
    while (getline(file, line)) {
        int i = 0;
        string id = "", name = "";

        if (line == "") {
            continue;
        }
        if (categoryCount >= maxCategories) {
            break;
        }

        while (i < line.length() && line[i] != ',') { //gets the id from category file 
            id += line[i];
            i++;
        }
        i++;

        while (i < line.length()) { //gets the name from categoryfile
            name += line[i];
            i++;
        }

        categories[categoryCount].setData(stoi(id), name); //categories array added an object of category in it
        categoryCount++;
    }
    file.close();
}

void Record::loadProducts() {
    string line;
    ifstream file("products.txt");

    if (!file) {
        cout << "Error opening products file" << endl;
        return;
    }

    getline(file, line);

    while (getline(file, line)) {

        if (line == "") {
            continue;
        }
        if (productCount >= maxProducts) {
            break;
        }

        string parts[5] = { "", "", "", "", "" };
        int p = 0;

        for (int i = 0; i < line.length(); i++) { //stores all manually
            if (line[i] == ',') {
                p++;
            }
            else {
                parts[p] += line[i];
            }
        }
        //stoi converts string to an integer
        products[productCount].setProduct(stoi(parts[0]), parts[1], stoi(parts[2]), stof(parts[3]), stoi(parts[4])); //adds an of products in the arra
        productCount++;
    }
    file.close();
}

string Record::getCategoryName(int id) {
    for (int i = 0; i < categoryCount; i++) {
        if (categories[i].getID() == id) { 
            return categories[i].getName(); //returns name of category that matches id
        }
    }
    return "Unknown";
}

int Record::getProductCount() {
    return productCount;
}

Product Record::getProduct(int index) {
    return products[index];
}

SearchFilter::SearchFilter(Record* r) {
    record = r;
}

void SearchFilter::showAll() {
    for (int i = 0; i < record->getProductCount(); i++) {
        Product p = record->getProduct(i); //loads the product
        p.display(record->getCategoryName(p.getCategoryId())); //calls category name and them displays the product 
    }
}

void SearchFilter::searchByName(string name) {
    cout << "Search Results:" << endl;

    for (int i = 0; i < record->getProductCount(); i++) {
        Product p = record->getProduct(i);
        if (p.getName().find(name) != string::npos) { //.find will either return true or npos if name is not found
            p.display(record->getCategoryName(p.getCategoryId()));
        }
    }
}

void SearchFilter::filterByCategory(int catId) {
    for (int i = 0; i < record->getProductCount(); i++) {
        Product p = record->getProduct(i);
        if (p.getCategoryId() == catId) 
            p.display(record->getCategoryName(catId));
        }
    }

void SearchFilter::filterByPrice(float min, float max) {
    for (int i = 0; i < record->getProductCount(); i++) {
        Product p = record->getProduct(i);
        if (p.getPrice() >= min && p.getPrice() <= max) {
            p.display(record->getCategoryName(p.getCategoryId()));
        }
    }
}

void SearchFilter::inStock() {
    for (int i = 0; i < record->getProductCount(); i++) {
        Product p = record->getProduct(i);
        if (p.getStock() > 0) {
            p.display(record->getCategoryName(p.getCategoryId()));
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
