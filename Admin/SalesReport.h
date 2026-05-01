#ifndef SALESREPORT_H
#define SALESREPORT_H
#include <string>
#include <fstream>

class SalesReport {
    std::string filename; 

public:
    SalesReport(std::string f);
    void generatetotalsalesreport();
};
#endif