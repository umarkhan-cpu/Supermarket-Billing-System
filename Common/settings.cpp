#include "settings.h"

#include<fstream>
#include<iostream>

using namespace std;

//                 Default settings 

string Settings::theme = "Light";
string Settings::language = "English";
string Settings::currency = "PKR";

//                load from file
void Settings::loadFromFile() {
	ifstream in("Data/settings.txt");
	if (!in)
		return;
	string line;
	while (getline(in, line)) {

		int equalPos = line.find('=');

		// skip line if '=' not found
		if (equalPos == -1) continue;

		// part before '=' is the key
		string key = line.substr(0, equalPos);

		//  part after equals '='  is value
		string value = line.substr(equalPos + 1);

		if (key == "theme") {
			setTheme(value);
		}
		else if (key == "language") {
			setLanguage(value);
		}
		else if (key == "currency") {
			setCurrency(value);
		}
	}
	in.close();
}
//                   save to  file
void Settings::saveToFile() {
	ofstream out("Data/settings.txt");

	out << "theme=" << theme << endl;
	out << "language=" << language << endl;
	out << "currency=" << currency << endl;

	out.close();
}

//                     Getters
string Settings::getTheme() {
	return theme;
}
string Settings::getLanguage() {
	return language;
}
string Settings::getCurrency() {
	return currency;
}

//                 Setters
bool Settings::setTheme(const std::string& t) {
	if (t == "Light" || t == "Dark") {
		theme = t;
		saveToFile();
		return true;
	}
	return false;
};
bool Settings::setLanguage(const std::string& l) {
	if (l == "English") {
		language = l;
		saveToFile();
		return true;
	}
	return false;
};
bool Settings::setCurrency(const std::string& c) {
	if (c == "PKR") {
		currency = c;
		saveToFile();
		return true;
	}
	return false;
};
//                Toggle Theme
void Settings::toggleTheme() {
	if (theme == "Light") {
		theme = "Dark";
	}
	else {
		theme = "Light";
	}

	saveToFile();
}