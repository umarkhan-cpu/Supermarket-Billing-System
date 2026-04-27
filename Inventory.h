#ifndef INVENTORY_H
#define INVENTORY_H

#include <fstream>

class Inventory { //       Inventory 
private:
    int productID;
    int quantity;

public:
    Inventory();
    Inventory(int productID, int quantity);

    //                   Getters 
    int getProductID() const;
    int getQuantity()  const;

    //                      Setters 
    bool setProductID(int productID);  // rejects non-positive values
    bool setQuantity(int quantity);    // rejects negative values

    // save and load 
    void saveToStream(std::ofstream& out) const;
    bool loadFromStream(std::ifstream& in);

    void display() const;
};

#endif // INVENTORY_H
