#ifndef FILTERANDSEARCH_H
#define FILTERANDSEARCH_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int PRODUCTS = 100;
const int CATEGORIES = 50;

class Category {

private:
    // ----- Attributes (encapsulated - accessed only through getters/setters) -----
    int categoryID;
    string categoryName;
    string categoryDesc;

public:
    // ----- Constructors -----

    Category();
    Category(int id, const string& name, const string& desc);
    Category(const Category& other);

    // ----- Getters (read access) -----
    int    getID() const;
    string getName() const;
    string getDescription() const;

    // ----- Setters (write access with basic validation) -----
    // Setters return bool so callers know if the value was accepted.
    // Validation rules:
    //   - ID must be positive (> 0)
    //   - Name must not be empty and must not contain commas (CSV safety)
    //   - Description must not contain commas (CSV safety) - may be empty
    bool setID(int id);
    bool setName(const string& name);
    bool setDescription(const string& desc);

    // ----- CSV serialization -----
    void setData(int id, string name);

    // Convert this object to a CSV line (no trailing newline).
    // Example return: "1,Dairy,Milk and cheese products"
    string toCSV() const;

    // Parse a CSV line into a Category object.
    // Static factory method - called as:  Category c = Category::fromCSV(line);
    // If the line is malformed, returns a Category with ID = 0 as an error signal.
    static Category fromCSV(const string& line);
};
/////////////////////////////

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
    string getName()const;
    int getCategoryId()const;
    float getPrice()const;
    int getStock()const;

	void addstock(int quantity);
	void removestock(int quantity);


	void save(std::ofstream& out);
	void load(std::ifstream& in);
    void display(const string& categoryName); //

	void setName(std::string n);
	void setCID(int c);
	void setPrice(float p);
	void setStock(int s);
};
////////////////////
class Record {
private:
    Product products[PRODUCTS];
    Category categories[CATEGORIES];

    int productCount;
    int categoryCount;

public:
    Record();
    void loadCategories();
    void loadProducts();
    string getCategoryName(int id);
    int getProductCount();
    Product getProduct(int index);
};

class SearchFilter {
private:
    Record* record;  

public:
    SearchFilter(Record* c);  
    void showAll();
    void searchByName(string name);
    void filterByCategory(int catId);
    void filterByPrice(float min, float max);
    void inStock();
};

#endif