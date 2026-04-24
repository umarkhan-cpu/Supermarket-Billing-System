
#ifndef PRODUCT_H
#define PRODUCT_H

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Product {
private:
	int ProductID;
	string name;
	int CategoryID;
	float price;
	int stock;

public:
	void setProduct(int PID, string n, int CID, float p, int s);
	int getPID();
	int getstock();

	void addstock(int quantity);
	void removestock(int quantity);

	void edit();

	void save(ofstream& out);
	void load(ifstream& in);
	void show();
};

#endif