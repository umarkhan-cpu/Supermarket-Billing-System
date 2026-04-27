#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
using std::string;

/*
 * Category — data class representing a single product category.
 *
 * Responsibilities:
 *   - Hold the data for ONE category (id, name, description)
 *   - Know how to serialize itself to/from a CSV line
 *
 * Non-responsibilities:
 *   - Does NOT manage a collection of categories (that's CategoryManagement's job)
 *   - Does NOT talk to files directly (only produces/consumes CSV strings)
 *
 * File format (one category per line in categories.txt):
 *   categoryID,categoryName,description
 *   e.g.  1,Dairy,Milk and cheese products
 */
class Category {

private:
    // ----- Attributes (encapsulated — accessed only through getters/setters) -----
    int categoryID;
    string categoryName;
    string categoryDesc;

public:
    // ----- Constructors -----

    // Default constructor: used when we need an "empty" Category
    // (e.g., when loading from file one by one)
    Category();

    // Parameterized constructor: used when we have all the data ready
    Category(int id, const string& name, const string& desc);

    // Copy constructor: used when we copy one Category to another
    // (e.g., when resizing the dynamic array in CategoryManagement).
    // Required because we'll be managing Category objects in a dynamic array.
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
    //   - Description must not contain commas (CSV safety) — may be empty
    bool setID(int id);
    bool setName(const string& name);
    bool setDescription(const string& desc);

    // ----- CSV serialization -----

    // Convert this object to a CSV line (no trailing newline).
    // Example return: "1,Dairy,Milk and cheese products"
    string toCSV() const;

    // Parse a CSV line into a Category object.
    // Static factory method — called as:  Category c = Category::fromCSV(line);
    // If the line is malformed, returns a Category with ID = -1 as an error signal.
    static Category fromCSV(const string& line);
};

#endif