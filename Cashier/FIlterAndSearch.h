#ifndef FILTERANDSEARCH_H
#define FILTERANDSEARCH_H

#include "..\Admin\ProductManagement.h"
#include "..\Admin\CategoryManagement.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class SearchFilter {
public:
    static void showAll();
    static void searchByName(const std::string& name);
    static void filterByCategory(int categoryID);
    static void filterByPrice(float min, float max);
    static void inStock();
    static void menu();
};


#endif