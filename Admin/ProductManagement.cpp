#include "ProductManagement.h"
#include <iostream>
#include <fstream>

// These are the main storage variables for all products
Product* ProductManagement::products = nullptr;
int      ProductManagement::count = 0;
int      ProductManagement::capacity = 0;

// File location where product data is stored
static const char* FILE_PATH = R"(C:\Users\mahno\OneDrive\Documents\GitHub\Supermarket-Billing-System\Data\products.txt)";


// This function finds the next ID by checking highest existing ID
int ProductManagement::nextAvailableID() {
    if (count == 0) return 1;

    int maxID = 0;
    for (int i = 0; i < count; i++) {
        if (products[i].getID() > maxID)
            maxID = products[i].getID();
    }
    return maxID + 1;
}


// Expands storage when array becomes full
void ProductManagement::growArray() {
    int newCapacity = (capacity == 0) ? 4 : capacity * 2;

    Product* newArr = new Product[newCapacity];

    for (int i = 0; i < count; i++)
        newArr[i] = products[i];

    delete[] products;
    products = newArr;
    capacity = newCapacity;
}


// Adds a new product into system
bool ProductManagement::addProduct(const std::string& name, int categoryID, float price, int stock) {

    Product temp;

    if (!temp.setName(name)) return false;
    if (!temp.setCategoryID(categoryID)) return false;
    if (!temp.setPrice(price)) return false;
    if (!temp.setStock(stock)) return false;

    if (count >= capacity)
        growArray();

    int newID = nextAvailableID();

    products[count] = Product(newID, name, categoryID, price, stock);
    count++;

    saveToFile();

    //std::cout << "Product added successfully with ID " << newID << "\n";
    return true;
}


// Updates an existing product
bool ProductManagement::editProduct(int id, const std::string& name, int categoryID, float price, int stock) {

    int index = findIndexByID(id);

    if (index == -1) {
        std::cout << "No product found with given ID\n";
        return false;
    }

    Product updated = products[index];

    if (!updated.setName(name)) return false;
    if (!updated.setCategoryID(categoryID)) return false;
    if (!updated.setPrice(price)) return false;
    if (!updated.setStock(stock)) return false;

    products[index] = updated;

    saveToFile();

    //std::cout << "Product updated successfully\n";
    return true;
}


// Deletes a product from system
bool ProductManagement::deleteProduct(int id) {

    int index = findIndexByID(id);

    if (index == -1) {
       // std::cout << "No product found with given ID\n";
        return false;
    }

    for (int i = index; i < count - 1; i++)
        products[i] = products[i + 1];

    count--;

    saveToFile();

    //std::cout << "Product deleted successfully\n";
    return true;
}


// Finds index of a product in array
int ProductManagement::findIndexByID(int id) {

    for (int i = 0; i < count; i++) {
        if (products[i].getID() == id)
            return i;
    }

    return -1;
}


// Returns product by ID
Product ProductManagement::findByID(int id) {

    int index = findIndexByID(id);

    if (index == -1)
        return Product();

    return products[index];
}


// Shows all products
/*void ProductManagement::viewAll() {

    if (count == 0) {
        std::cout << "No products available\n";
        return;
    }

    for (int i = 0; i < count; i++)
        products[i].display();
}
*/


// Loads data from file into memory
void ProductManagement::loadFromFile() {

    std::ifstream in(FILE_PATH);

    if (!in.is_open())
        return;

    delete[] products;
    products = nullptr;
    count = 0;
    capacity = 0;

    Product temp;

    while (temp.loadFromStream(in)) {

        if (count >= capacity)
            growArray();

        products[count++] = temp;
    }

    in.close();
}


// Saves all products into file
void ProductManagement::saveToFile() {

    std::ofstream out(FILE_PATH);

    if (!out.is_open()) {
        std::cout << "File error while saving products\n";
        return;
    }

    for (int i = 0; i < count; i++)
        products[i].saveToStream(out);

    out.close();
}


// Frees memory before program ends
void ProductManagement::cleanup() {

    delete[] products;
    products = nullptr;
    count = 0;
    capacity = 0;
}


// Returns total product count
int ProductManagement::getCount() {
    return count;
}


// Gives direct access to product at index
Product& ProductManagement::getAt(int index) {
    return products[index];
}