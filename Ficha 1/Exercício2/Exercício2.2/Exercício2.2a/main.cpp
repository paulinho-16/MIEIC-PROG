#include <iostream>
using namespace std;
int main()
{
	double a, b, c;
	double maximo, minimo,medio;
	cout << "Enter the first number: ";
	cin >> a;
	cout << "Enter the second number: ";
	cin >> b;
	cout << "Enter the third number: ";
	cin >> c;
	// Alinea a)
	if ((a >= b) && (a >= c))
	{
		maximo = a;
		if (b <= c)
			{
				minimo = b;
				medio = c;
				cout << "The largest number is " << a << ", and the smallest number is " << b << "." << endl;
			}
		else
			{
				minimo = c;
				medio = b;
				cout << "The largest number is " << a << ", and the smallest number is " << c << "." << endl;
			}
	}
	else
	{
		if ((b > a) && (b > c))
		{
			maximo = b;
			if (a <= c)
			{
				minimo = a;
				medio = c;
				cout << "The largest number is " << b << ", and the smallest number is " << a << "." << endl;
			}
			else
			{
				minimo = c;
				medio = a;
				cout << "The largest number is " << b << ", and the smallest number is " << c << "." << endl;
			}
		}
		else
		{
			maximo = c;
				if (a <= b)
				{
						minimo = a;
						medio = b;
						cout << "The largest number is " << c << ", and the smallest number is " << a << "." << endl;
				}
				else
				{
					minimo = b;
					medio = a;
					cout << "The largest number is " << c << ", and the smallest number is " << b << "." << endl;
				}
		}
	}
	// Alinea b)
	cout << "By decreasing order: " << maximo << " > " << medio << " > " << minimo << endl;
	// Alinea c)
	if (minimo + medio <= maximo)
		cout << "Not possible to build a triangle with these lengths." << endl;
	else
		cout << "Possible to build a triangle with these lenghts. " << endl;
	_getwch();
	return 0;
}