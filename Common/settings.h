#ifndef SETTINGS_H
#define SETTINGS_H

#include<string>

class Settings {
private:

	static std::string theme; //theme
	static std::string language;  //language
	static std::string currency;  //currency

public:
	//load and save
	static void loadFromFile();
	static void saveToFile();

	//getters
	static std::string getTheme();
	static std::string getLanguage();
	static std::string getCurrency();

	//setters
	static bool setTheme(const std::string& t);
	static bool setLanguage(const std::string& l);
	static bool setCurrency(const std::string& c);

	//toggle theme
	static void toggleTheme();

};
#endif
