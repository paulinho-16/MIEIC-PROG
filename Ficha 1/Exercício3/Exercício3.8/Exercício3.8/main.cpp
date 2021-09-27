#include <iostream>
using namespace std;

int mdc(int m, int n)
{
	if (m % n == 0)
		return n;
	return mdc(n, m % n);
}

int main()
{
	int n1, n2;
	cout << "Enter 2 numbers (n1 n2): ";
	cin >> n1 >> n2;
	cout << "The greatest common divisor of these numbers is: " << mdc(n1, n2) << endl;
	system("pause");
	return 0;
}