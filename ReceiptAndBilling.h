#ifndef RECEIPTANDBILLING_H
#define RECEIPTANDBILLING_H

#include <iostream>
#include <string>
#include <fstream>
#include "Product.h"
#include "ProductManagement.h"
#include "DiscountManagement.h"
#include "Transaction.h"
#include "TransactionManagement.h"
using namespace std;

class Bill;
class Receipt;

class CartItem { // Represents a single item in the cart with its product and quantity
public:
    Product product;
    int quantity;
private:
    CartItem();
    CartItem(Product p, int q);
    double getPrice() const;
};

class Cart { // Manages a collection of CartItems with dynamic memory
public:
    CartItem* cartItems;// array of cart items
    int totalcount;
    int capacity;

    Cart();
    ~Cart();
    void resize(); // doubles capacity when cart is full
    int itemIndex(int productID) const;
    void addItem(Product p, int quant);
    void removeItem(int productID);
    void updateQuantity(int productID, int newQuan);
    double getTotal() const;
    void displayCart() const;
};

class CartStorage { // Handles saving and loading cart data to/from a file
private:
    string cartFile;

public:
    CartStorage(string file);
    void saveCart(const Cart& cart) const; // saves cart items as CSV
    void loadCart(Cart& cart) const; // loads cart items from CSV
};

class Bill { // Calculates and displays a bill for a customer
public:
    string billID;
    string customerName;
    Cart& cartReference; // reference to the cart being billed
    double taxRate;
    double discountAmount;
    double subtotal;
    double totalAmount;

    Bill(const string& name, Cart& cart, double tax, const string& couponCode);
    void calculate();
    void display() const;
    void generateReceipt(Receipt& r);
    static void menu();
};

class Receipt { // Builds and stores a formatted receipt from a Bill
private:
    string* receiptLines; // array of receipt lines
    int totalLines;
    int capacity;

public:
    Receipt();
    Receipt(Bill& bill);
    ~Receipt();
    void addLine(const string& line);
    void receipt(Bill& bill);
    void printToConsole() const;
    void saveToFile(const string& filename) const;
};

#endif