#include "SalesReport.h"
#include <iostream>
#include <fstream>
using namespace std; 
SalesReport::SalesReport(string f) {
    filename = f;
}
void SalesReport::generatetotalsalesreport() {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No sales data found. (File doesn't exist)" << endl;
        return;
    }

    //transaction class wil be used here 

    cout << "Reading sales data" << endl;
    file.close();
}