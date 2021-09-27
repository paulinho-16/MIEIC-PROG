#include "Date.h"
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

Date::Date()
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	year = 1900 + newtime.tm_year;
	month = 1 + newtime.tm_mon;
	day = newtime.tm_mday;
}

Date::Date(unsigned int year, unsigned int month, unsigned int day)
{
	this->year = year;
	this->month = month;
	this->day = day;
}

Date::Date(string yearMonthDay)
{
	this->year = stoi(yearMonthDay.substr(0, 4));
	this->month = stoi(yearMonthDay.substr(5, 2));
	this->day = stoi(yearMonthDay.substr(8, 2));
}

void Date::setYear(unsigned int year)
{
	this->year = year;
}

void Date::setMonth(unsigned int month)
{
	this->month = month;
}

void Date::setDay(unsigned int day)
{
	this->day = day;
}

void Date::setDate(unsigned int year, unsigned int month, unsigned int day)
{
	this->year = year;
	this->month = month;
	this->day = day;
}

unsigned int Date::getYear() const
{
	return year;
}

unsigned int Date::getMonth() const
{
	return month;
}

unsigned int Date::getDay() const
{
	return day;
}

string Date::getDate() const
{
	return to_string(this->year) + "/" + to_string(this->month) + "/" + to_string(this->day);
}

void Date::show() const
{
	cout << getDate();
}

unsigned int Date::Dias_Mes() const
{
	vector<int> dias;
	if (month < 1 || month > 12)
		return 0;
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		dias = { 31,29,31,30,31,30,31,31,30,31,30,31 };
		return dias[month - 1];
	}
	else
	{
		dias = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return dias[month - 1];
	}
}

bool Date::isValid() const
{
	unsigned int n_dias = Dias_Mes();
	if (year < 0 || month < 1 || month > 12 || day < 1 || day > n_dias)
		return false;
	return true;
}

bool Date::isEqualTo(const Date &date) const
{
	if (year == date.year && month == date.month && day == date.day)
		return true;
	return false;
}

bool Date::isNotEqualTo(const Date &date) const
{
	if (year == date.year && month == date.month && day == date.day)
		return false;
	return true;
}

bool Date::isAfter(const Date &date) const
{
	if (year > date.year)
		return true;
	if (year == date.year && month > date.month)
		return true;
	if (year == date.year && month == date.month && day > date.day)
		return true;
	return false;
}

bool Date::isBefore(const Date &date) const
{
	if (year < date.year)
		return true;
	if (year == date.year && month < date.month)
		return true;
	if (year == date.year && month == date.month && day < date.day)
		return true;
	return false;
}