#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <fstream>

class Transaction {
private:
	int TransactionID;
	std::string date;
	int CashierID;
	float TotalAmount;
	std::string status;

public:
	Transaction();

	void setData(int TID, std::string D, int CID, float amount, std::string st);

	//Getters
	int getID() const;
	std::string getDate() const;
	int getCashierID() const;
	float getTotalAmount() const;
	std::string getStatus() const;
	
	//show
	void show() const;

	//save and load 
	void save(std::ofstream &out);
	void load(std::ifstream& in);

}; 
#endif
