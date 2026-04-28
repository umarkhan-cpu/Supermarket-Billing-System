#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <fstream>

class Product {
private:
    int id;
    std::string name;
    int categoryID;
    float price;
    int stock;

public:
    // Default constructor 

    Product();

    // constructor for product 
    Product(int id, const std::string& name, int categoryID, float price, int stock);

    //           Getters 
    int         getID()         const;
    std::string getName()       const;
    int         getCategoryID() const;
    float       getPrice()      const;
    int         getStock()      const;

    //                  Setters
    bool setName(const std::string& name);   // rejects empty strings and names with commas
    bool setCategoryID(int categoryID);      // rejects non-positive values
    bool setPrice(float price);             // rejects negative prices
    bool setStock(int stock);               // rejects negative stock counts

    //             save to stream
    void saveToStream(std::ofstream& out) const;

    //           load from stream
    bool loadFromStream(std::ifstream& in);

    //                       display
    void display() const;
};

#endif // PRODUCT_H