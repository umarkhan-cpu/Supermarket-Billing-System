//#ifndef FILTERANDSEARCH_H
//#define FILTERANDSEARCH_H
//
// #include "ProductManagement.h"
//#include "CategoryManagement.h"

//#include <iostream>
//#include <fstream>
//#include <string>
//
//using namespace std;
//
//class Record {
//private:
//    Product* products;      
//    Category* categories; 
//    int productCount;
//    int categoryCount;
//    int maxProducts;        
//    int maxCategories;
//
//    int productCount;
//    int categoryCount;
//
//public:
//    Record(int maxP = 100, int maxC = 50); 
//    ~Record();
//    void loadCategories();
//    void loadProducts();
//    string getCategoryName(int id);
//    int getProductCount();
//    Product getProduct(int index);
//};
//
//class SearchFilter {
//private:
//    Record* record;  
//
//public:
//    SearchFilter(Record* c);  
//    void showAll();
//    void searchByName(string name);
//    void filterByCategory(int catId);
//    void filterByPrice(float min, float max);
//    void inStock();
//};
//
//#endif