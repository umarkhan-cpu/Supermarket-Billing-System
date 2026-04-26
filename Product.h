
#ifndef PRODUCT_H
#define PRODUCT_H

#include<iostream>
#include<fstream>
#include<string>


class Product {
private:
	int ProductID;
	std::string name;
	int CategoryID;
	float price;
	int stock;

public:
	void setProduct(int PID, std::string n, int CID, float p, int s);
	int getPID() const;
	int getstock() const;

	void addstock(int quantity);
	void removestock(int quantity);


	void save(std::ofstream& out);
	void load(std::ifstream& in);
	void show();

	void setName(std::string n);
	void setCID(int c);
	void setPrice(float p);
	void setStock(int s);
};

#endif