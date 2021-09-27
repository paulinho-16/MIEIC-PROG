#include "Product.h"
using namespace std;

Product::Product()
{
	this->description = "Default";
	this->price = 0.0;
}

Product::Product(string description, double price)
{
	this->description = description;
	this->price = price;
}

string Product::getDescription()
{
	return this->description;
}

double Product::getPrice()
{
	return this->price;
}

void Product::setDescription(string description)
{
	this->description = description;
}

void Product::setPrice(double price)
{
	this->price = price;
}