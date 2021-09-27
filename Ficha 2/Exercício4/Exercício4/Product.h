#pragma once

#include <string>
using namespace std;

class Product
{
	private:
		string description;
		double price;
	public:
		Product();
		Product(string description, double price);
		string getDescription();
		double getPrice();
		void setDescription(string description);
		void setPrice(double price);
};