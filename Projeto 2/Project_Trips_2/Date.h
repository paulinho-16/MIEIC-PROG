#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "defs.h"

using namespace std;

class Date 
{
private:
	unsigned  day;
	unsigned  month;
	unsigned  year;

public:
	Date();
	Date(string s);
	Date(unsigned year, unsigned  month, unsigned  day);

	// GET methods
	unsigned  getDay() const;
	unsigned  getMonth() const;
	unsigned getYear() const;
	
	// SET methods
	void setDay(unsigned  day);
	void setMonth(unsigned  month);
	void setYear(unsigned year);

	// other methods
	string toString() const;
	string toReverseString() const;
	bool verify_input(string s) const;	
	
	// Methods for comparing Dates
	friend bool operator == (const Date& left, const Date& right);
	friend bool operator <= (const Date& left, const Date& right);
	friend bool operator >= (const Date& left, const Date& right);
};