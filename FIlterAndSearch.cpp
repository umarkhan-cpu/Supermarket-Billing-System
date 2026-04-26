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
        if (p.getCategoryId() == catId) {
            p.display(record->getCategoryName(catId));
        }
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

