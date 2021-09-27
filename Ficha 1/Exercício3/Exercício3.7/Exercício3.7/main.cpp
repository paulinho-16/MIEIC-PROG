#include <iostream>
using namespace std;

long int factorial_ite(int n)
{
	long int result = 1;
	for (int i = n; i >= 1; i--)
		result *= i;
	return result;
}

long int factorial_rec(int n)
{
	if (n <= 1)
		return 1;
	return n * factorial_rec(n - 1);
}

int main()
{
	cout << factorial_ite(5) << endl;
	cout << factorial_rec(5) << endl;
	system("pause");
	return 0;
}