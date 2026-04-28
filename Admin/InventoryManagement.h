#ifndef INVENTORY_MANAGEMENT_H
#define INVENTORY_MANAGEMENT_H

#include "Inventory.h"


class InventoryManagement {
private:
    static Inventory* records;   // dynamic array of inventory records
    static int        count;
    static int        capacity;

    // Grows the backing array when we hit capacity
    static void growArray();

    // Returns array index for productID, or -1 if not found
   
    static int findIndexByProductID(int productID);

public:
    InventoryManagement() = delete;

    // Add And Remove  Stock operations 
    static bool addStock(int productID, int amount);     // increase stock
    static bool removeStock(int productID, int amount);  // decrease stock; fails if it would go negative

    //    check low stock

    static void checkLowStock(int threshold = 5);  
  
    // prints every inventory record
    static void viewAll();                         

    //              save and load 
    static void loadFromFile();
    static void saveToFile();

    //            cleanup
    static void cleanup();
};

#endif // INVENTORY_MANAGEMENT_H