#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <string>
using std::string;

class Discount 
{

private:
    int    couponID;
    string couponCode;
    string type;       // "PERCENTAGE" or "FIXED"
    float  value;
    bool   isActive;

    // helper function to format a floating value while converting to string
    static string formatFloat(float f); 

public:
    // ----- Constructors -----
    Discount();
    Discount(int id, const string& code, const string& type, float value, bool isActive);
    Discount(const Discount& other);

    // ----- Getters -----
    int    getID() const;
    string getCode() const;
    string getType() const;
    float  getValue() const;
    bool   getIsActive() const;

    // ----- Setters (with validation, return bool) -----
    // Validation rules:
    //   - ID must be positive (> 0)
    //   - Code must be non-empty, no commas, no spaces (CSV + UX safety)
    //   - Type must be exactly "PERCENTAGE" or "FIXED"
    //   - Value must be > 0 (and for PERCENTAGE, <= 100)
    //   - isActive accepts any bool
    bool setID(int id);
    bool setCode(const string& code);
    bool setType(const string& type);
    bool setValue(float value);
    bool setIsActive(bool active);

    // ----- Discount calculation -----

    // Given a bill subtotal, returns the discount amount in rupees.
    // For PERCENTAGE: subtotal * (value / 100)
    // For FIXED:     value (capped at subtotal so discount never exceeds bill)
    // Returns 0 if this discount is inactive.
    float calculateDiscount(float subtotal) const;

    // ----- CSV Serialization -----
    string toCSV() const; 
    static Discount fromCSV(const string& line);
};

#endif
