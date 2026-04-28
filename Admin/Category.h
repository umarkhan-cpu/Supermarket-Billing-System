#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
using std::string;

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

    // Convert this object to a CSV line (no trailing newline).
    // Example return: "1,Dairy,Milk and cheese products"
    string toCSV() const;

    // Parse a CSV line into a Category object.
    // Static factory method - called as:  Category c = Category::fromCSV(line);
    // If the line is malformed, returns a Category with ID = 0 as an error signal.
    static Category fromCSV(const string& line);
};

#endif