#include "Category.h"
#include <sstream>
using namespace std;

Category::Category() : categoryID(0), categoryName(""), categoryDesc("") {}

Category::Category(int id, const string& name, const string& desc) : categoryID(0), categoryName(""), categoryDesc("")
{
	setID(id);
	setName(name);
	setDescription(desc);
}

Category::Category(const Category& other) : categoryID(other.categoryID), 
											categoryName(other.categoryName),
											categoryDesc(other.categoryDesc) {}

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

bool Category::setID(int id)
{
	if (id > 0)
	{
		categoryID = id;
		return true;
	}
	return false;
}

bool Category::setName(const string& name)
{
	if (name != "" && name.find(',') == name.npos)
	{
		categoryName = name;
		return true;
	}
	return false;
}

bool Category::setDescription(const string& desc)
{
	if (desc.find(',') == desc.npos)
	{
		categoryDesc = desc;
		return true;
	}
	return false;
}

// Returns a default Category (id = 0) if the line is malformed,
// so callers can skip invalid entries without crashing.
Category Category::fromCSV(const string& line) {
	stringstream ss(line);
	string idStr, name, desc;

	getline(ss, idStr, ',');
	getline(ss, name, ',');
	getline(ss, desc);

	if (idStr.empty() || name.empty()) return Category();

	try {
		return Category(stoi(idStr), name, desc);
	}
	catch (const invalid_argument&) { return Category(); }
	catch (const out_of_range&) { return Category(); }
}
