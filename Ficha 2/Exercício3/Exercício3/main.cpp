#include <iostream>
#include "Person.h"
using namespace std;

int main()
{	
	Person p1;
	cout << p1.getname() << endl << p1.getgender() << endl;
	p1.getdate().show();
	Date d1 = Date(2000, 10, 16);
	Person p2("Paulinho", "Masculino", d1);
	cout << endl << p2.getname() << endl << p2.getgender() << endl;
	p2.getdate().show();
	Date d2 = Date(2019, 5, 15);
	p1.setname("Maria");
	p1.setgender("Feminino");
	p1.setdate(d2);
	cout << endl << p1.getname() << endl << p1.getgender() << endl;
	p1.getdate().show();
	return 0;
}