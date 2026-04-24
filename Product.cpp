#include "Product.h"
#include<string>

// Product setup
void Product::setProduct(int PID, string n, int CID, float p, int s) {
	ProductID = PID;
	name = n;
	CategoryID = CID;
	price = p;
	stock = s;
}

int Product::getPID() { return ProductID; }
int Product::getstock() { return stock; }

// Add and remove stocks 
void Product::addstock(int quantity) { stock += quantity; }
void Product::removestock(int quantity) { stock -= quantity; }

// Edit stock
void Product::edit() {
	cout << "New Name:\n";
	cin >> name;
	cout << "New Category ID: \n";
	cin >> CategoryID;
	cout << "New Price:\n";
	cin >> price;
	cout << "New stock:\n";
	cin >> stock;
}

// Save
void Product::save(ofstream& out) {
	out << ProductID << " "
		<< name << " "
		<< CategoryID << " "
		<< price << " "
		<< stock << " " << endl;
}

// Load
void Product::load(ifstream& in) {
	in >> ProductID >> name >> CategoryID >> price >> stock;
}

// Show
void Product::show() {
	cout << ProductID << "|" << name << "|"
		<< CategoryID << "|" << price << "|"
		<< "|" << stock << endl;
}