#include <iostream>
using namespace std;
int main()
{
	int n,q;
	float j,total = 0;
	cout << "Enter the number of years of deposit: ";
	cin >> n;
	cout << "Enter the amount of money you deposit in a year: ";
	cin >> q;
	cout << "Enter the annual interest rate, in %: ";
	cin >> j;
	for (int i = 1; i <= n; i++)
		total += q + q * j / 100;
	cout << "The total amount of money after " << n << " years is: " << total << " euros" << endl;
	system("pause");
	return 0;
}