
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "defs.h"
#include "Address.h"		
	
using namespace std;

Address::Address()
{
	this->street = "street";
	this->doorNumber = "doorNumber";
	this->floor = "floor";
	this->postalCode = "postalCode";
	this->location = "location";
};

Address::Address(string street, string doorNumber, string floor, string postalCode, string location)
{
	this->street = street;
	this->doorNumber = doorNumber; 
	this->floor = floor; 
	this->postalCode = postalCode; 
	this->location = location;
};

Address::Address(string info)
{
	stringstream ss(info);
	string item;
	vector<string> addr;
	while (getline(ss, item, '/'))
	{
		if (item[0] == ' ')
			item.erase(0, 1);
		if (item[item.size() - 1] == ' ')
			item.pop_back();
		addr.push_back(item);
	}
	this->street = addr[0];
	this->doorNumber = addr[1];
	this->floor = addr[2];
	this->postalCode = addr[3];
	this->location = addr[4];
};

// methods GET
string Address::getStreet() const { return this->street; };
string Address::getDoorNumber() const { return this->doorNumber; };
string Address::getFloor() const { return this->floor; };
string Address::getPostalCode() const { return this->postalCode; };
string Address::getLocation() const { return this->location; };

// methods SET
void Address::setStreet(string street) { this->street = street ; };
void Address::setDoorNumber(string doorNumber) { this->doorNumber = doorNumber ; };
void Address::setFloor(string floor) { this->floor = floor; };
void Address::setPostalCode(string postalCode) { this->postalCode = postalCode; };
void Address::setLocation(string  location) { this->location = location; };

string Address::toString() 
{
	string s = this->street + " / " + this->doorNumber + " / " + this->floor + " / " + this->postalCode + " / " + this->location;
	return s;
};