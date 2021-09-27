#include "Person.h"

Person::Person()
{
	this->name = "NoName";
	this->gender = "NoGender";
	this->birthdate = Date();
}

Person::Person(string name, string gender, Date date)
{
	this->name = name;
	this->gender = gender;
	this->birthdate = date;
}

string Person::getname() const
{
	return this->name;
}

string Person::getgender() const
{
	return this->gender;
}

Date Person::getdate() const
{
	return birthdate;
}

void Person::setname(string name)
{
	this->name = name;
}

void Person::setgender(string gender)
{
	this->gender = gender;
}

void Person::setdate(Date date)
{
	this->birthdate = date;
}