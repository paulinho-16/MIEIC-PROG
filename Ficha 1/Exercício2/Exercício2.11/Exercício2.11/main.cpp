#include <iostream>
#include <cmath>
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
			int n;
			double soma = 0;
			cout << "Enter the n term of the serie, to calculate the sum of the first n terms: ";
			cin >> n;
			int impar = -1;
			for (int i = 0; i < n; i++)
			{
				double termo = pow(-1, i) * 4 * (1 / double(impar + 2));
				impar += 2;
				soma += termo;
			}
			cout << "The sum of the first " << n << " terms of this serie is " << soma << endl;
			break;
		}
		case 'b':
		{
			int n;
			double termo = 1, soma = 1;
			cout << "Enter the n term of the serie, to calculate the sum of the first n terms: ";
			cin >> n;
			if (n == 1)
				cout << "The sum of the first " << n << " terms of this serie is " << soma << endl;
			else
			{
				for (int i = 1; i < n; i++)
				{
					termo = termo * (1.0 / i);
					soma += termo;
				}
				cout << "The sum of the first " << n << " terms of this serie is " << soma << endl;
			}
			break;
		}
		case 'c':
		{
			int n;
			double x, termo = 1, soma = 1;
			cout << "Enter the n term of the serie, to calculate the sum of the first n terms: ";
			cin >> n;
			cout << "Enter the value of a positive number x, for the function e^(-x): ";
			cin >> x;
			if (n == 1)
				cout << "The sum of the first " << n << " terms of this serie is " << soma << endl;
			else
			{
				for (int i = 1; i < n; i++)
				{
					termo = pow(-1, i) * abs(termo) * (x / double(i));
					soma += termo;
				}
				cout << "The sum of the first " << n << " terms of this serie is " << soma << endl;
			}
			break;
		}
	}
	system("pause");
	return 0;
}