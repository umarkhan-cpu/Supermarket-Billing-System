#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "..\Admin\Product.h"
#include "..\Admin\ProductManagement.h"
#include "..\Admin\CategoryManagement.h"
#include "RefundManagement.h"
#include "DiscountManagement.h"
#include "TransactionManagement.h"
using namespace std;
const int MAX_CART_ITEMS = 100;

class CartItem {
public:
    Product product;
    int quantity;

    CartItem();
    CartItem(Product p, int q);
    double getPrice() const;  
};

class Cart {
public:
    CartItem cartItems[MAX_CART_ITEMS];
    int totalcount;

    Cart();
    void   addItem(Product p, int qty);
    void   removeItem(int productID);
    void   updateQuantity(int productID, int newQty);
    double getTotal() const;
    void   displayCart() const;

private:
    int itemIndex(int productID) const;   
};

class CartStorage {
public:
    CartStorage(string cartFile = "Data/cart.txt");
    void saveCart(const Cart& cart) const;
    void loadCart(Cart& cart) const;

private:
    string cartFile;
};


class Receipt;// forward declaration

class Bill {
public:
    string customerName;
    string billID;
    double subtotal;
    double taxRate;
    double discountAmount;
    double totalAmount;
    Cart& cartReference;

    Bill(const string& customerName,Cart& cart,double taxRate = 0.05, const string& couponCode = "");
    void calculate();
    void display() const;
    void generateReceipt(Receipt& r);
    static void menu();
};

const int MAX_RECEIPT_LINES = 50;

class Receipt {
public:
    Receipt();
    explicit Receipt(Bill& bill);
    void receipt(Bill& bill);
    void printToConsole() const;
    void saveToFile(const string& filename) const;

private:
    string receiptLines[MAX_RECEIPT_LINES];
    int totalLines;

    void addLine(const string& line); 
};