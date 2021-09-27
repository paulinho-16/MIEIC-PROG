#include <iostream>
#include <cmath>
using namespace std;

double integrateTR(double f(double), double a, double b, int n)
{
	double result = 0;
	double h = (b - a) / double(n);
	for (int i = 1; i <= n; i++)
	{
		double area = (h / 2.0)*(f(a + (i - 1)*h) + f(a + i * h));
		result += area;
	}
	return result;
}

double g(double x)
{
	return x * x;
}

double h(double x)
{
	return sqrt(4 - x * x);
}

int main()
{
	for (int j = 1; j <= 7; j++)
	{
		cout << integrateTR(g, 0, 10, pow(2,j)) << endl;
		cout << integrateTR(h, -2, 2, pow(2,j)) << endl;
	}
	system("pause");
	return 0;
}