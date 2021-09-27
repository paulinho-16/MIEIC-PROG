#include <iostream>
#include <cmath>
using namespace std;

double round(double x, unsigned n)
{
	x = floor(x*pow(10, n) + 0.5) / pow(10, n);
	return x;
}

int main()
{
	double number;
	int decimais;
	cout << "Enter a number to round: ";
	cin >> number;
	cout << "Enter the number of decimal places of the rounding: ";
	cin >> decimais;
	cout << "Rounded number: " << round(number, decimais) << endl;
	system("pause");
	return 0;
}