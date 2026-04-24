#ifndef INVENTORY_H
#define INVENTORY_H

#include "Product.h"
#include<string>
using namespace std;

class Inventory {
private:
	Product* products;
	int totalItems;
	int lowStocklimit;

public:
	Inventory();

	void addproduct(int id, string name, int CID, float price, int stock);
	void deleteProduct(int id);
	void viewAll();

	void addstock(int id, int quantity);
	void removestock(int id, int quantity);
	void checklowstock();

	void savetoFile();
	void loadfromfile();

	~Inventory();
};

#endif
