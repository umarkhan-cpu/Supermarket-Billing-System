#include "Inventory.h"
#include <iostream>
#include<fstream>
#include<string>

Inventory::Inventory() {
	products = NULL;
	totalItems = 0;
	lowStocklimit = 5;
}

// Add product
void Inventory::addproduct(int id,std::string name, int CID, float price, int stock) {
	Product* temp = new Product[totalItems + 1];
	for (int i = 0; i < totalItems; i++) {
		temp[i] = products[i];
	}
	temp[totalItems].setProduct(id, name, CID, price, stock);
	delete[] products;
	products = temp;
	totalItems++;
}

// Delete product
void Inventory::deleteProduct(int id) {
	int index = -1;
	for (int i = 0; i < totalItems; i++) {
		if (products[i].getPID() == id) {
			index = i;
			break;
		}
	}
	if (index == -1) return;

	Product* temp = new Product[totalItems - 1];

	for (int i = 0, j = 0; i < totalItems; i++) {
		if (i != index) {
			temp[j++] = products[i];
		}
	}

	delete[] products;
	products = temp;
	totalItems--;
}

// View all
void Inventory::viewAll() {
	std::cout << "\n-------INVENTORY---------\n";
	for (int i = 0; i < totalItems; i++) {
		products[i].show();
	}
}

// Stock operations
void Inventory::addstock(int id, int quantity) {
	for (int i = 0; i < totalItems; i++) {
		if (products[i].getPID() == id) {
			products[i].addstock(quantity);
		}
	}
}

void Inventory::removestock(int id, int quantity) {
	for (int i = 0; i < totalItems; i++) {
		if (products[i].getPID() == id) {
			products[i].removestock(quantity);
		}
	}
}

void Inventory::checklowstock() {
	std::cout << "\n----Low Stock Itmes-----\n";
	for (int i = 0; i < totalItems; i++) {
		if (products[i].getstock() <= lowStocklimit) {
			products[i].show();
		}
	}
}

// Save to file
void Inventory::savetoFile() {
	std::ofstream out("products.txt");

	for (int i = 0; i < totalItems; i++) {
		products[i].save(out);
	}
	out.close();
}

// Load from file
void Inventory::loadfromfile() {
	std::ifstream in("products.txt");

	// clear old data first
	delete[] products;
	products = NULL;
	totalItems = 0;

	int id, CID, stock;
	float price;
	std::string name;

	while (in >> id >> name >> CID >> price >> stock) {
		addproduct(id, name, CID, price, stock);
	}
	in.close();
}

bool Inventory::editProduct(int id, std::string newName, int newCID, float newPrice, int newStock) {
	for (int i = 0; i < totalItems; i++) {
		if (products[i].getPID() == id) {
			products[i].setName(newName);
			products[i].setCID(newCID);
			products[i].setPrice(newPrice);
			products[i].setStock(newStock);
			return true;
		}
	}
	return false;
}

// Destructor
Inventory::~Inventory() {
	delete[] products;
	products = NULL;
}