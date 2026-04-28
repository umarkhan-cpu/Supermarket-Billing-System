#include "InventoryManagement.h"
#include "ProductManagement.h"
#include <iostream>
#include <fstream>

//               Static variables 
Inventory* InventoryManagement::records = nullptr;
int        InventoryManagement::count = 0;
int        InventoryManagement::capacity = 0;

// file path for inventory data
static const char* INV_FILE_PATH = "Data/inventory.txt";


//  Resize array when it gets full 
void InventoryManagement::growArray() {
    int newCapacity;

    if (capacity == 0) {
        newCapacity = 4;        
    }
    else {
        newCapacity = capacity * 2;   
    }
    Inventory* bigger = new Inventory[newCapacity];

    // copy old data into new bigger array
    for (int i = 0; i < count; i++)
        bigger[i] = records[i];

    delete[] records;   // delete old memory
    records = bigger;   // point to new array
    capacity = newCapacity;
}


//Find record index using product ID 
int InventoryManagement::findIndexByProductID(int productID) {
    for (int i = 0; i < count; i++) {
        if (records[i].getProductID() == productID)
            return i;
    }
    return -1; // not found
}


//    Add stock
bool InventoryManagement::addStock(int productID, int amount) {

    
    if (amount <= 0) {
        std::cout << "Error: amount to add must be greater than zero.\n";
        return false;
    }

    // check if product actually exists
    Product p = ProductManagement::findByID(productID);
    if (p.getID() == 0) {
        std::cout << "Error: product with ID " << productID << " does not exist.\n";
        return false;
    }

    int index = findIndexByProductID(productID);

    if (index == -1) {
        // first time adding stock ? create new record
        if (count >= capacity) growArray();

        records[count] = Inventory(productID, amount);
        count++;
    }
    else {
        // record exists ? just increase quantity
        int newQty = records[index].getQuantity() + amount;
        records[index].setQuantity(newQty);
    }

    // also update product's stock so both stay synced
    int syncedStock = p.getStock() + amount;

    ProductManagement::editProduct(
        productID,
        p.getName(),
        p.getCategoryID(),
        p.getPrice(),
        syncedStock
    );

    saveToFile();

    std::cout << amount << " unit(s) added to product "
        << productID << ". New stock: " << syncedStock << ".\n";

    return true;
}


//  Remove stock 
bool InventoryManagement::removeStock(int productID, int amount) {

    if (amount <= 0) {
        std::cout << "Error: amount to remove must be greater than zero.\n";
        return false;
    }

    // check product exists
    Product p = ProductManagement::findByID(productID);
    if (p.getID() == 0) {
        std::cout << "Error: product with ID " << productID << " does not exist.\n";
        return false;
    }

    // make sure enough stock is available
    if (p.getStock() < amount) {
        std::cout << "Error: not enough stock. Available: "
            << p.getStock() << ", requested: " << amount << ".\n";
        return false;
    }

    int index = findIndexByProductID(productID);

    if (index == -1) {
        // safety check (shouldn't normally happen)
        std::cout << "Error: no inventory record found for product "
            << productID << ".\n";
        return false;
    }

    // reduce quantity
    int newQty = records[index].getQuantity() - amount;
    records[index].setQuantity(newQty);

    // sync with ProductManagement
    int syncedStock = p.getStock() - amount;

    ProductManagement::editProduct(
        productID,
        p.getName(),
        p.getCategoryID(),
        p.getPrice(),
        syncedStock
    );

    saveToFile();

    std::cout << amount << " unit(s) removed from product "
        << productID << ". Remaining stock: "
        << syncedStock << ".\n";

    return true;
}


//           Show low stock products
void InventoryManagement::checkLowStock(int threshold) {

    std::cout << "\n--- Low Stock Report (threshold: "
        << threshold << ") ---\n";

    bool anyFound = false;

    for (int i = 0; i < count; i++) {

        if (records[i].getQuantity() <= threshold) {

            // get product name from ProductManagement
            Product p = ProductManagement::findByID(records[i].getProductID());

            std::string name = (p.getID() != 0)
                ? p.getName()
                : "(unknown)";

            std::cout << "ProductID: " << records[i].getProductID()
                << " | Name: " << name
                << " | Stock: " << records[i].getQuantity() << "\n";

            anyFound = true;
        }
    }

    if (!anyFound)
        std::cout << "All products are sufficiently stocked.\n";

    std::cout << "---------------------------------------------------\n";
}


//          View all inventory records 
void InventoryManagement::viewAll() {

    if (count == 0) {
        std::cout << "No inventory records found.\n";
        return;
    }

    std::cout << "\n--- Inventory Records ---\n";

    for (int i = 0; i < count; i++)
        records[i].display();

    std::cout << "-------------------------\n";
}


//             Load from file 
void InventoryManagement::loadFromFile() {

    std::ifstream in(INV_FILE_PATH);

    if (!in.is_open()) return;  // first run ? file may not exist

    // clear previous data
    delete[] records;
    records = nullptr;
    count = 0;
    capacity = 0;

    Inventory temp;

    // read all records
    while (temp.loadFromStream(in)) {
        if (count >= capacity) growArray();
        records[count++] = temp;
    }

    in.close();
}


// ===== Save to file =====
void InventoryManagement::saveToFile() {

    std::ofstream out(INV_FILE_PATH);

    if (!out.is_open()) {
        std::cout << "Warning: could not open file for writing.\n";
        return;
    }

    for (int i = 0; i < count; i++)
        records[i].saveToStream(out);

    out.close();
}


// Free memory before program ends 
void InventoryManagement::cleanup() {

    delete[] records;

    records = nullptr;
    count = 0;
    capacity = 0;
}