#include "Discount.h"
#include <sstream>
using namespace std;

// ============================================================================
// Constructors
// ============================================================================

Discount::Discount() : couponID(0), couponCode(""), value(0), type(""), isActive(false) {}

Discount::Discount(int id, const string& code, const string& type, float value, bool isActive) 
                   : couponID(0), couponCode(""), value(0), type(""), isActive(false)
{
    setID(id);
    setCode(code);
    setType(type);
    setValue(value);
    setIsActive(isActive);
}

Discount::Discount(const Discount& other)
    : couponID(other.couponID),
      couponCode(other.couponCode),
      type(other.type),
      value(other.value),
      isActive(other.isActive){
}

// ============================================================================
// Getters
// ============================================================================

int Discount::getID() const
{
    return couponID;
}

string Discount::getCode() const
{
    return couponCode;
}

string Discount::getType() const
{
    return type;
}

float Discount::getValue() const
{
    return value;
}

bool Discount::getIsActive() const
{
    return isActive;
}

// ============================================================================
// Setters
// ============================================================================

bool Discount::setID(int id)
{
    if (id > 0) // ID must be > 0
    {
        couponID = id;
        return true;
    }
    return false;
}

bool Discount::setCode(const string& code)
{
    // Coupon code must not be empty or have ',' or ' '
    if (code != "" && code.find(',') == code.npos && code.find(' ') == code.npos)
    {
        couponCode = code;
        return true;
    }
    return false;
}

bool Discount::setType(const string& type)
{
    if (type == "PERCENTAGE" || type == "FIXED") // Exactly 2 types are allowed
    {
        this->type = type;
        return true;
    }
    return false;
}

bool Discount::setValue(float value)
{
    if (value <= 0) return false; // Value must be > 0

    if (type == "PERCENTAGE" && value > 100) return false; // PERCENTAGE value cannot be > 100

    this->value = value;

    return true;
}

bool Discount::setIsActive(bool active)
{
    isActive = active;
    return true; // return true to be consistent with other setters
}

// ============================================================================
// Discount Calculation
// ============================================================================

float Discount::calculateDiscount(float subtotal) const
{
    if (!isActive) return 0; // Coupon is inactive

    if (type == "PERCENTAGE") return subtotal * (value / 100); // Discount in percentage

    if (type == "FIXED") return (value < subtotal) ? value : subtotal; // Return value if value < subtotal, otherwise, return subtotal (e.g. a Rs. 500 coupon on a Rs. 100 bill returns 100, not 500)

    return 0;
}

// ============================================================================
// CSV Serialization
// ============================================================================

// Formats a float without trailing zeros: 20.0 -> "20", 20.5 -> "20.5"
string Discount::formatFloat(float f)
{
    ostringstream oss;
    oss << f;
    return oss.str();
}

string Discount::toCSV() const
{
    string status;
    if (isActive)
        status = "Active";
    else
        status = "Inactive"; 

    string line = to_string(couponID) + "," + couponCode + "," + type + "," + formatFloat(value) +  "," + status;

    return line;
}

Discount Discount::fromCSV(const string& line)
{
    stringstream ss(line);
    string idStr, code, type, valueStr, status;
    
    getline(ss, idStr, ',');
    getline(ss, code, ',');
    getline(ss, type, ',');
    getline(ss, valueStr, ',');
    getline(ss, status);

    if (idStr.empty() || code.empty() || type.empty() || valueStr.empty()) return Discount();

    // Try/catch method to handle invalid_argument or out_of_range value
    // thrown by stoi or stof, in which case a default object is returned
    try
    {
        int id = stoi(idStr);
        float value = stof(valueStr);
        bool isActive = false;

        if (status == "Active")
            isActive = true;  
        else
            isActive = false;

        return Discount(id, code, type, value, isActive);
    }
    catch (const invalid_argument&) { return Discount(); }
    catch (const out_of_range&) { return Discount(); }
}