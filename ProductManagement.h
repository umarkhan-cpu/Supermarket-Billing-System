#ifndef PRODUCT_MANAGEMENT_H
#define PRODUCT_MANAGEMENT_H

#include "Product.h"
#include <string>

class ProductManagement {
private:
    static Product* products;   
    static int      count;      
    static int      capacity;   

    // Finds the next available product ID 
    static int nextAvailableID();

    // Expands array when it gets  full
    static void growArray();

public:
    
    ProductManagement() = delete;

      static bool addProduct(const std::string& name, int categoryID, float price, int stock);
    static bool editProduct(int id, const std::string& name, int categoryID, float price, int stock);
    static bool deleteProduct(int id);

    // Searching and viewing
    static Product  findByID(int id);
    static int      findIndexByID(int id);
    static void     viewAll();

   //save and load
    static void loadFromFile();
    static void saveToFile();

    // Clears memory 
    static void cleanup();

    static int      getCount();
    static Product& getAt(int index);
};

#endif