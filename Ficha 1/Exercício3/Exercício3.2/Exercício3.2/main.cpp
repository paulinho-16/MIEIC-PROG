#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

bool isPrime(int numero)
{
	if (numero == 1)
		return false;
	int contador = 0;
	for (int i = 2; i <= floor(sqrt(numero)); i++)
	{
		if (numero%i == 0)
			contador++;
	}
	if (contador > 0)
		return false;
	return true;
}

int main()
{
	char alinea;
	cout << "Choose the alinea (a,b or c): ";
	cin >> alinea;
	cout << endl;
	switch (alinea)
	{
		case 'a':     //alinea a
		{
			int numero;
			cout << "Enter a number: ";
			cin >> numero;
			if (isPrime(numero))
				cout << "The number " << numero << " is prime." << endl;
			else
				cout << "The number " << numero << " isn't prime." << endl;
			break;
		}
		case 'b':     //alinea b
		{
			int primos = 0;
			for (int i = 2; primos < 100; i++)
			{
				if (isPrime(i))
				{
					cout << setw(5) << i << endl;
					primos++;
				}
			}
			break;
		}
		case 'c':     //alinea c
		{
			for (int i = 2; i < 10000; i++)
			{
				if (isPrime(i))
					cout << setw(5) << i << endl;
			}
			break;
		}
	}
	system("pause");
	return 0;
}