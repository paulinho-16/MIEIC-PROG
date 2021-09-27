
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "defs.h"
#include "Date.h"
#include "Packet.h"

using namespace std;

vector<string> Packet::props_id = // vector to store the properties' id
	{		
		"Id: ",
		"Locals: ",
		"Begin Date : " ,
		"End Date: ",
		"Price (Per Person): ",
		"Max People: ",
		"Current People: "
	}; 

vector<string> Packet::props_default = // vector to store default properties to be read
	{ 
	    " (default: 1000) ",
		" (default: Default - Def1, Def2, Def3) ",
		" (default: 1999/1/1) " ,
		" (default: 1999/1/1) ",
		" (default: 1000.0 ) ",
		" (default: 100 ) ",
		" (default: 0 )"
	}; 

Packet::Packet() 
{
	this->id = 1000;
	this->sites = "Default - Def1, Def2, Def3";
	this->begin = Date();
	this->end = Date();
	this->pricePerPerson = 1000.0;
	this->maxPeople = 100;
	this->currentPeople = 0;

	this->all_props = {
		to_string(this->id),
		this->sites,
		this->begin.toString(),
		this->end.toString(),
		to_string(this->pricePerPerson),
		to_string(this->maxPeople),
		to_string(this->currentPeople)
	};
};

Packet::Packet(int id, string sites, Date begin, Date end, double pricePerPerson, unsigned maxPeople, unsigned currentPeople) 
{
	this->id = id;
	this->sites = sites;
	this->begin = begin;
	this->end = end;
	this->pricePerPerson = pricePerPerson;
	this->maxPeople = maxPeople;
	this->currentPeople = currentPeople;

	this->all_props = {
		to_string(this->id),
		this->sites, 
		this->begin.toString(), 
		this->end.toString(), 
		to_string(this->pricePerPerson), 
		to_string(this->maxPeople),
		to_string(this->currentPeople)
	};
};

// GET methods
int Packet::getId() const { return this->id; };
string Packet::getSites() const { return this->sites; };
Date Packet::getBeginDate() const { return this->begin; };
Date Packet::getEndDate() const { return this->end; };
double Packet::getPricePerPerson() const { return this->pricePerPerson; };
unsigned Packet::getMaxPeople() const { return this->maxPeople; };
unsigned Packet::getCurrentPeople() const { return this->currentPeople; };

vector<string> Packet::getAllProps() 
{
	this->all_props = {
		to_string(this->id),
		this->sites,
		this->begin.toString(),
		this->end.toString(),
		to_string(this->pricePerPerson),
		to_string(this->maxPeople),
		to_string(this->currentPeople)
	};
	return this->all_props;
};

// SET methods
void Packet::setId(int id) { this->id = id; };  // to set negative if "deprecated"
void Packet::setSites(string sites) { this->sites = sites; };
void Packet::setBeginDate(Date begin) { this->begin = begin; };
void Packet::setEndDate(Date end) { this->end = end; };
void Packet::setPricePerPerson(double pricePerPerson) { this->pricePerPerson = pricePerPerson; };
void Packet::setMaxPeople(unsigned maxPersons) { this->maxPeople = maxPeople; };
void Packet::setCurrentPeople(unsigned currentPeople) { this->currentPeople = currentPeople; };

/**
Get a vector with all sites of the packet
*/
vector<string> Packet::spec_sites() 
{
	string sites = this->sites;
	sites.erase(sites.begin(), sites.begin() + sites.find_first_of("-") + 2);

	stringstream ss(sites);
	string item = "";
	vector<string> addr;
	while (getline(ss, item, ','))
	{
		if (item[0] == ' ')
			item.erase(0, 1);
		if (item[item.size() - 1] == ' ')
			item.pop_back();
		addr.push_back(item);
	}
	return addr;
};

/**
Verifies input when managing Packet Info.
@return True if everything is ok, False otherwise.*/
bool Packet::verify_input(string s, int o) const 
{
	if (s.empty())
		return false;
	if (o == 0) // Check Id
	{
		bool isalnm = true;
		for (int j = 0; j < s.length(); j++) {
			int c = s[j];
			if (!isdigit(c) && c != int('-'))
				isalnm = false;
		}
		return isalnm;
	}
	else if (o == 2 || o == 3) // Check Begin and End Date
	{
		bool isaldgt = true;
		for (int j = 0; j < s.length(); j++) {
			int c = s[j];
			if (!isdigit(c) && c != int('/'))
				isaldgt = false;
		}
		return isaldgt;
	}
	else if (o == 4 || o == 5 || o == 6) // Check price, max people and current people
	{
		bool isaldgt = true;
		for (int j = 0; j < s.length(); j++) {
			int c = s[j];
			if (!isdigit(c) && c != int('.') )
				isaldgt = false;
		}
		return isaldgt;
	}
	return true;
};

/**
Instructions to Operator Overload.
@param pack Packet with Vector of Packages to overload operator <<.
*/
ostream& operator<<(ostream& out, Packet& pack) 
{
	vector<string> v = pack.getAllProps();

	for (int i = 0; i < v.size(); i++) {
		out << "\t" << pack.props_id[i] << v[i] << "\n";
	}
	return out;
};

ostream& operator<<=(ostream& out, Packet& pack) 
{
	vector<string> v = pack.getAllProps();

	for (int i = 0; i < 2; i++) {
		out << "\t" << pack.props_id[i] << v[i] << "\n";
	}
	return out;
};

