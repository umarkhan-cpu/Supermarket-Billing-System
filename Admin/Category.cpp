#include "Category.h"
#include <sstream>
using namespace std;

// ============================================================================
// Constructors
// ============================================================================

Category::Category() : categoryID(0), categoryName(""), categoryDesc("") {}

Category::Category(int id, const string& name, const string& desc)
    : categoryID(0), categoryName(""), categoryDesc("")
{
    // Route through setters so validation rules are enforced during construction.
    setID(id);
    setName(name);
    setDescription(desc);
}

Category::Category(const Category& other)
    : categoryID(other.categoryID),
    categoryName(other.categoryName),
    categoryDesc(other.categoryDesc) {
}

// ============================================================================
// Getters
// ============================================================================

int Category::getID() const
{
    return categoryID;
}

string Category::getName() const
{
    return categoryName;
}

string Category::getDescription() const
{
    return categoryDesc;
}

// ============================================================================
// Setters
// ============================================================================

bool Category::setID(int id)
{
    if (id > 0)
    {
        categoryID = id;
        return true;
    }
    return false;
}

// Names must be non-empty and must not contain commas (CSV safety).
bool Category::setName(const string& name)
{
    if (name != "" && name.find(',') == name.npos)
    {
        categoryName = name;
        return true;
    }
    return false;
}

// Descriptions are optional but must not contain commas (CSV safety).
bool Category::setDescription(const string& desc)
{
    if (desc.find(',') == desc.npos)
    {
        categoryDesc = desc;
        return true;
    }
    return false;
}

// ============================================================================
// CSV Serialization (to be used when writing int Data/categories.txt
// ============================================================================

string Category::toCSV() const
{
    string line = to_string(categoryID) + "," + categoryName + "," + categoryDesc;
    return line;
}

// If the line is malformed, returns a default Category (ID = 0) instead of
// throwing. This lets callers skip bad lines in the file and keep reading,
// without wrapping every call in try/catch.
Category Category::fromCSV(const string& line)
{
    stringstream ss(line);
    string idStr, name, desc;

    getline(ss, idStr, ',');
    getline(ss, name, ',');
    getline(ss, desc);

    if (idStr.empty() || name.empty()) return Category();

    // stoi throws if the string is not a number, or if the number is too
    // large to fit in an int. Both are treated as parse failures.
    try
    {
        return Category(stoi(idStr), name, desc);
    }
    catch (const invalid_argument&) { return Category(); }
    catch (const out_of_range&) { return Category(); }
}