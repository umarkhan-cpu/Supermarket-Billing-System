#include "Product.h"
#include <iostream>

//  Constructors 

Product::Product()
    : id(0), name(""), categoryID(0), price(0.0f), stock(0) {
}

Product::Product(int id, const std::string& name, int categoryID, float price, int stock)
    : id(id), name(name), categoryID(categoryID), price(price), stock(stock) {
}


// Getters 

int Product::getID() const { return id; }

std::string Product::getName() const { return name; }

int Product::getCategoryID() const { return categoryID; }

float Product::getPrice() const { return price; }

int Product::getStock() const { return stock; }


//         Setters 

bool Product::setName(const std::string& newName) {
    if (newName.empty()) {
        std::cout << "Error: product name cannot be empty.\n";
        return false;
    }

    if (newName.find(',') != std::string::npos) {
        std::cout << "Error: product name cannot contain commas.\n";
        return false;
    }

    name = newName;
    return true;
}

bool Product::setCategoryID(int newCategoryID) {
    if (newCategoryID <= 0) {
        std::cout << "Error: category ID must be positive.\n";
        return false;
    }

    categoryID = newCategoryID;
    return true;
}

bool Product::setPrice(float newPrice) {
    if (newPrice < 0) {
        std::cout << "Error: price cannot be negative.\n";
        return false;
    }

    price = newPrice;
    return true;
}

bool Product::setStock(int newStock) {
    if (newStock < 0) {
        std::cout << "Error: stock cannot be negative.\n";
        return false;
    }

    stock = newStock;
    return true;
}


// save
void Product::saveToStream(std::ofstream& out) const {
    out << id << ","
        << name << ","
        << categoryID << ","
        << price << ","
        << stock << "\n";
}


//             load
bool Product::loadFromStream(std::ifstream& in) {

    std::string line;
    if (!std::getline(in, line))
        return false;

    if (line.empty())
        return false;

    int pos;
    std::string field;

    // ---- ID ----
    pos = line.find(',');
    if (pos == std::string::npos) return false;

    field = line.substr(0, pos);
    id = std::stoi(field);
    line = line.substr(pos + 1);

    // ---- Name ----
    pos = line.find(',');
    if (pos == std::string::npos) return false;

    name = line.substr(0, pos);
    line = line.substr(pos + 1);

    // ---- Category ID ----
    pos = line.find(',');
    if (pos == std::string::npos) return false;

    field = line.substr(0, pos);
    categoryID = std::stoi(field);
    line = line.substr(pos + 1);

    // ---- Price ----
    pos = line.find(',');
    if (pos == std::string::npos) return false;

    field = line.substr(0, pos);
    price = std::stof(field);
    line = line.substr(pos + 1);

    // ---- Stock ----
    stock = std::stoi(line);

    return true;
}


//         Display 

void Product::display() const {
    std::cout << "ID: " << id
        << " | Name: " << name
        << " | Category: " << categoryID
        << " | Price: " << price
        << " | Stock: " << stock << "\n";
}