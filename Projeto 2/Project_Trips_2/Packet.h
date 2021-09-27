#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "defs.h"
#include "Date.h"

using namespace std;

class Packet 
{
private:
	int id; // packet unique identifier
	string sites; // touristic sites to visit
	Date begin;  // begin date
	Date end;  // end date
	double pricePerPerson; // price per person
	unsigned maxPeople; // maximum number of people accepted
	unsigned currentPeople; // number of persons still available in the packet (updated whenever the packet is sold to a new client)
	vector<string> all_props; // vector to store all object's properties as strings

public:
	static vector<string> props_id; // vector to store the properties' id
	static vector<string> props_default; // vector to store default properties to be read
	
	Packet();
	Packet(int id, string sites, Date begin, Date end, double pricePerPerson , unsigned maxPeople, unsigned currentPeople);

	// GET methods
	int getId() const;
	string getSites() const;
	Date getBeginDate() const;
	Date getEndDate() const;
	double getPricePerPerson() const;
	unsigned getMaxPeople() const;
	unsigned getCurrentPeople() const;
	vector<string> getAllProps();

	// SET methods
	void setId(int id);  // set negative if "deprecated"
	void setSites(string sites);
	void setBeginDate(Date begin);
	void setEndDate(Date end);
	void setPricePerPerson(double pricePerPerson);
	void setMaxPeople(unsigned maxPersons);
	void setCurrentPeople(unsigned currentPeople);

	//other methods
	vector<string> spec_sites();
	bool verify_input(string s, int o) const;
	friend ostream& operator<<(ostream& out, Packet &pack);
	friend ostream& operator<<=(ostream& out, Packet& pack);

};
