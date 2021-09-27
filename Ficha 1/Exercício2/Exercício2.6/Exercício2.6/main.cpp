#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
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
			int contador = 0;
			for (int i = 2; i <= floor(sqrt(numero)); i++)
			{
				if (numero%i == 0)
					contador++;
			}
			if (contador > 0)
				cout << "The number " << numero << " isn't prime." << endl;
			else if (numero == 1)
				cout << "The number " << numero << " isn't prime." << endl;
			else
				cout << "The number " << numero << " is prime." << endl;
			break;
		}
		case 'b':     //alinea b
		{
			int primos = 0;
			for (int i = 2; primos < 100; i++)
			{
				int contador = 0;
				for (int j = 2; j < i; j++)
				{
					if (i%j == 0)
						contador++;
				}
				if (contador == 0)
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
				int contador = 0;
				for (int j = 2; j < i; j++)
					if (i%j == 0)
						contador++;
				if (contador == 0)
					cout << setw(5) << i << endl;
			}
			break;
		}
	}
	system("pause");
	return 0;
}