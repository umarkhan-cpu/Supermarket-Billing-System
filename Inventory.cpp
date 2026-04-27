#include "Inventory.h"
#include <iostream>
#include <sstream>


//                    Constructors

Inventory::Inventory() : productID(0), quantity(0) {}

Inventory::Inventory(int productID, int quantity)
    : productID(productID), quantity(quantity) {
}

//                        Getters 
int Inventory::getProductID() const { return productID; }
int Inventory::getQuantity()  const { return quantity; }


//                       Setters

bool Inventory::setProductID(int newProductID) {
    if (newProductID <= 0) {
        std::cout << "Error: product ID must be a positive number.\n";
        return false;
    }
    productID = newProductID;
    return true;
}

bool Inventory::setQuantity(int newQuantity) {
    if (newQuantity < 0) {
        std::cout << "Error: quantity cannot be negative.\n";
        return false;
    }
    quantity = newQuantity;
    return true;
}


//                        Save 
void Inventory::saveToStream(std::ofstream& out) const {
   
    // Format: productID,quantity
    out << productID << "," << quantity << "\n";
}

//                       Load
bool Inventory::loadFromStream(std::ifstream& in) {
    std::string line;
    if (!std::getline(in, line) || line.empty())
        return false;

    std::istringstream row(line);
    std::string field;

    try {
        if (!std::getline(row, field, ',')) return false;
        productID = std::stoi(field);

        if (!std::getline(row, field, ',')) return false;
        quantity = std::stoi(field);
    }
    catch (...) {
        return false;
    }

    return true;
}


//                  Display

void Inventory::display() const {
    std::cout << "ProductID: " << productID
        << " | Quantity: " << quantity << "\n";
}
