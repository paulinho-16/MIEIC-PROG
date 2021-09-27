#ifndef DATE_H
#define DATE_H
#include <string>
using namespace std;

class Date
{
	public:
		Date();
		Date(unsigned int year, unsigned int month, unsigned int day);
		Date(string yearMonthDay); // yearMonthDay must be in format "yyyy/mm/dd"
		void setYear(unsigned int year);
		void setMonth(unsigned int month);
		void setDay(unsigned int day);
		void setDate(unsigned int year, unsigned int month, unsigned int day);
		unsigned int getYear() const;
		unsigned int getMonth() const;
		unsigned int getDay() const;
		string getDate() const;  // returns the date in format "yyyy/mm/dd"
		void show() const; // shows the date on the screen in format "yyyy/mm/dd"
		bool isValid() const;
		bool isEqualTo(const Date &date) const;
		bool isNotEqualTo(const Date &date) const;
		bool isAfter(const Date &date) const;
		bool isBefore(const Date &date) const;
	private:
		unsigned int year;
		unsigned int month;
		unsigned int day;
		unsigned int Dias_Mes() const;
};

#endif