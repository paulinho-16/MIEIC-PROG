#include <iostream>
#include "Date.h"
using namespace std;

int main()
{
	Date data1 = Date(2018, 4, 30);
	data1.show();
	cout << endl;
	data1.setYear(2019);
	data1.setMonth(10);
	data1.setDay(16);
	data1.show();
	cout << endl;
	Date data2 = Date("2020/11/04");
	cout << data2.getDate() << endl;
	data2.show();
	cout << endl;
	cout << data1.isValid() << endl;
	cout << data2.isValid() << endl;
	data2.setDate(2012, 5, 4);
	data1.show();
	cout << endl;
	data2.show();
	cout << endl << data1.isEqualTo(data2) << endl;
	cout << data2.isNotEqualTo(data1) << endl;
	cout << data1.isAfter(data2) << endl;
	cout << data1.isBefore(data1) << endl;
	// Because every class constructor requires parameters until now (no default constructor)
	Date data3;
	data3.show();
	cout << endl;
	system("pause");
	return 0;
}