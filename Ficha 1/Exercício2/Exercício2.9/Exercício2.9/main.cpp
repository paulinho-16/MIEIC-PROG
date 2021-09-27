#include <iostream>
using namespace std;
int main()
{
	char alinea;
	cout << "Enter the alinea you want to do: ";
	cin >> alinea;
	switch (alinea)
	{
		case 'a':
		{
			int soma = 0 , minimo = 99999999 , maximo = -99999999 , comprimento = 0 , valor = 1;
			double media;
			while (valor != 0)
			{
				cout << "Enter an integer number (0 to end): ";
				cin >> valor;
				if (valor == 0)
				{
					cout << "End of sequence." << endl;
					break;
				}
				soma += valor;
				if (valor < minimo)
					minimo = valor;
				if (valor > maximo)
					maximo = valor;
				comprimento++;
			}
			media = static_cast<double>(soma) / comprimento;
			cout << "The sum of the " << comprimento << " entered numbers is " << soma << ", the minimum is " << minimo << ", the maximum is " << maximo << ", and the mean is " << media << endl;
			break;
		}
		case 'b':
		{
			int comprimento, soma = 0, minimo = 99999999, maximo = -99999999, valor;
			double media;
			cout << "Enter the length of the sequence: ";
			cin >> comprimento;
			for (int i = 1; i <= comprimento; i++)
			{
				cout << "Enter an integer number: ";
				cin >> valor;
				soma += valor;
				if (valor < minimo)
					minimo = valor;
				if (valor > maximo)
					maximo = valor;
			}
			media = static_cast<double>(soma) / comprimento;
			cout << "The sum of the " << comprimento << " entered numbers is " << soma << ", the minimum is " << minimo << ", the maximum is " << maximo << ", and the mean is " << media << endl;
			break;
		}
		case 'c':
		{
			int comprimento = 0 , soma = 0, minimo = 99999999, maximo = -99999999, valor;
			double media;
			while (true)
			{
				cout << "Enter an integer number (Ctrl + Z to end): ";
				cin >> valor;
				if (cin.fail())
					if (cin.eof())
						break;
				soma += valor;
				if (valor < minimo)
					minimo = valor;
				if (valor > maximo)
					maximo = valor;
				comprimento++;
			}
			media = static_cast<double>(soma) / comprimento;
			cout << "The sum of the " << comprimento << " entered numbers is " << soma << ", the minimum is " << minimo << ", the maximum is " << maximo << ", and the mean is " << media << endl;
			break;
		}
	}
	system("pause");
	return 0;
}