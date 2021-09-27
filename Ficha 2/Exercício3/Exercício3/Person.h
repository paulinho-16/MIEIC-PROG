#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "Date.h"
using namespace std;

class Person
{
	private:
		string name;
		string gender;
		Date birthdate;
	public:
		Person();
		Person(string name, string gender, Date date);
		string getname() const;
		string getgender() const;
		Date getdate() const;
		void setname(string name);
		void setgender(string gender);
		void setdate(Date date);
};

#endif