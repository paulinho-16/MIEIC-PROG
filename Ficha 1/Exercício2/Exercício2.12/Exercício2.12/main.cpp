#include <iostream>
#include <cmath>
#include <iomanip>
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
			double n , soma = 0 , variacao , soma_antiga;
			cout << "Enter the precision of the variation of the sums: ";
			cin >> n;
			int impar = -1 , i = 0 , n_termos = 0 ;
			variacao = 100000;
			while (abs(variacao) >= n)
			{
				double termo = pow(-1, i) * 4 * (1 / double(impar + 2));
				n_termos++;
				impar += 2;
				soma_antiga = soma;
				soma += termo;
				variacao = soma - soma_antiga;
				i++;
			}
			cout << "The sum of the first " << n_termos << " terms of this serie is " << fixed << setprecision(20) << soma << endl;
			break;
		}
		case 'b':
		{
			double termo = 1, soma = 1, n , variacao , soma_antiga;
			int i = 1, n_termos = 0;
			cout << "Enter the precision of the variation of the sums: ";
			cin >> n;
			variacao = 100000;
			while(abs(variacao) >= n)
			{
				termo = termo * (1.0 / i);
				n_termos++;
				soma_antiga = soma;
				soma += termo;
				variacao = soma - soma_antiga;
				i++;
			}
			cout << "The sum of the first " << n_termos << " terms of this serie is " << fixed << setprecision(20) << soma << endl;
			break;
		}
		case 'c':
		{
			int i = 1 , n_termos = 0;
			double x , termo = 1 , soma = 1 , n , variacao , soma_antiga;
			cout << "Enter the precision of the variation of the sums: ";
			cin >> n;
			cout << "Enter the value of a positive number x, for the function e^(-x): ";
			cin >> x;
			variacao = 100000;
			while(abs(variacao) >= n)
			{
				termo = pow(-1, i) * abs(termo) * (x / double(i));
				n_termos++;
				soma_antiga = soma;
				soma += termo;
				variacao = soma - soma_antiga;
				i++;
			}
			cout << "The sum of the first " << n_termos << " terms of this serie is " << fixed << setprecision(20) << soma << endl;
			break;
		}
	}
	system("pause");
	return 0;
}