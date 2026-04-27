#ifndef RECEIPTANDBILLING_H
#define RECEIPTANDBILLING_H

#include "ProductManagement.h"
#include "CategoryManagement.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace std;

const int MAX_CART_ITEMS = 100;
const int MAX_RECEIPT_LINES = 200;
const int MAX_PRODUCTS = 100;

class CartItem {
public:
    Product product;
    int quantity;

    CartItem();
    CartItem(Product p, int q);

    double getprice();
};

class Cart {
public:
    CartItem cartItems[MAX_CART_ITEMS];
    int totalcount;

    Cart();

    int itemindex(int productID);
    void addItem(Product p, int qty);
    void removeItem(int productID);
    void updateQuantity(int productID, int newQty);
    double getTotal();
    void displayCart();
};

class CartStorage {
public:
    string productsFile;
    string cartFile;

    CartStorage(string pFile = "products.txt", string cFile = "cart.txt");

    int loadProducts(Product products[]);
    void saveCart(Cart& cart);
    bool findProductById(int targetId, Product& result);
    void loadCart(Cart& cart);
};

class Receipt;

class Bill {
public:
    string billID;
    string customerName;
    string billDate;
    double subtotal;
    double taxRate;
    double discountAmount;
    double totalAmount;
    Cart& cartReference;

    Bill(string n, Cart& cart, double tax = 0.17, double discount = 0.0);

    void calculate();
    void display() const;
    void generateReceipt(Receipt& r);
    void menu();
};

class Receipt {
public:
    string billID;
    string customerName;
    string receiptDate;
    string receiptLines[MAX_RECEIPT_LINES];
    int totalLines;

    Receipt();
    Receipt(Bill& bill);

    void addline(string line);
    void receipt(Bill& bill);
    void printToConsole() const;
    void saveToFile(string filename) const;
};

void userInputCart(Cart& cart, Product products[], int productCount);

#endif