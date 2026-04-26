#include "Product.h"
#include<iostream>
#include<string>

// Product setup
void Product::setProduct(int PID,std::string n, int CID, float p, int s) {
	ProductID = PID;
	name = n;
	CategoryID = CID;
	price = p;
	stock = s;
}

int Product::getPID() const { return ProductID; }
int Product::getstock() const { return stock; }

// Add and remove stocks 
void Product::addstock(int quantity) { stock += quantity; }
void Product::removestock(int quantity) { stock -= quantity; }



// Save
void Product::save(std::ofstream& out) {
	out << ProductID << " "
		<< name << " "
		<< CategoryID << " "
		<< price << " "
		<< stock << " " << endl;
}

// Load
void Product::load(std::ifstream& in) {
	in >> ProductID >> name >> CategoryID >> price >> stock;
}

// Show
void Product::show() {
	std::cout << ProductID << "|" << name << "|"
		<< CategoryID << "|" << price << "|"
		<< "|" << stock << std::endl;
}

//new setters

void Product::setName(std::string n) { name = n; }
void Product::setCID(int c) { CategoryID = c; }
void Product::setPrice(float p) { price = p; }
void Product::setStock(int s) { stock = s; }

