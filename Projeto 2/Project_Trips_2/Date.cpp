
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "defs.h"
#include "Date.h"

using namespace std;

Date::Date() 
{
	this->day = 1;
	this->month = 1;
	this->year = 1999;

};
Date::Date(unsigned year, unsigned  month, unsigned  day) 
{
	this->day = day;
	this->month = month;
	this->year = year;
};

Date::Date(string s ) 
{
	stringstream ss(s);
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
	this->year = stoi(addr[0]);
	this->month = stoi(addr[1]);
	this->day = stoi(addr[2]);
};

// GET methods
unsigned  Date::getDay() const { return this->day; };
unsigned  Date::getMonth() const { return this->month; };
unsigned Date::getYear() const { return this->year; };

// SET methods

void Date::setDay(unsigned  day) { this->day = day; };
void Date::setMonth(unsigned  month) { this->month = month; };
void Date::setYear(unsigned year) { this->year = year; };

// other methods
string Date::toString() const
{
	int year = this->getYear();
	int month = this->getMonth();
	int day = this->getDay();

	string s = to_string(year) + "/" + to_string(month) + "/" + to_string(day);

	return s;

};

string Date::toReverseString() const 
{
	string l = to_string(this->day) + "/" + to_string(this->month) + "/" + to_string(this->year);
	return l;
};

bool Date::verify_input(string s) const 
{
	bool isaldgt = true;
	for (int j = 0; j < s.length(); j++) 
	{
		int c = s[j];
		if (!isdigit(c) && c != int('/'))
			isaldgt = false;
	}
	return isaldgt;
};

bool operator == (const Date& left, const Date& right) 
{
	if (left.year != right.year)
		return false;
	if (left.month != right.month)
		return false;
	if (left.day != right.day)
		return false;
	return true;
};

bool operator <= (const Date& left, const Date& right) 
{
	if (left == right)
		return true;
	else 
	{
		if (right.year < left.year)
			return false;
		if (right.year == left.year && right.month < left.month)
			return false;
		if (right.year == left.year && right.month == left.month && right.day < left.day)
			return false;

		return true;
	}
};
bool operator >= (const Date& left, const Date& right) 
{
	if (left == right)
		return true;
	else 
	{
		if (right.year > left.year)
			return false;
		if (right.year == left.year && right.month > left.month)
			return false;
		if (right.year == left.year && right.month == left.month && right.day > left.day)
			return false;

		return true;

	}
};

