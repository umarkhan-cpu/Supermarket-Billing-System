#ifndef INVENTORY_H
#define INVENTORY_H

#include "Product.h"
#include<string>


class Inventory {
private:
	Product* products;
	int totalItems;
	int lowStocklimit;

public:
	Inventory();

	void addproduct(int id,std:: string name, int CID, float price, int stock);
	void deleteProduct(int id);
	void viewAll();

	void addstock(int id, int quantity);
	void removestock(int id, int quantity);
	void checklowstock();

	void savetoFile();
	void loadfromfile();

	bool editProduct(int id, std::string newName, int newCID, float newPrice, int newStock);

	~Inventory();
};

#endif
