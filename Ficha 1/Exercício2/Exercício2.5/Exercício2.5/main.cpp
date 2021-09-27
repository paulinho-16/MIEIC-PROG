#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main()
{
	double a, b, c, result1, result2,parte_real,parte_imaginaria;
	cout << "Enter the value of a, in the equation: ";
	cin >> a;
	cout << "Enter the value of b, in the equation: ";
	cin >> b;
	cout << "Enter the value of c, in the equation: ";
	cin >> c;
	cout << fixed << setprecision(3);
	if (b*b - 4 * a*c > 0)
	{
		result1 = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
		result2 = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);
		cout << "This equation has 2 different real roots, with the values: " << result1 << " and " << result2 << endl;
	}
	else if (b*b - 4 * a*c == 0)
	{
		result1 = (-b / (2 * a));
		cout << "This equation has 2 equal real roots, with the value: " << result1 << endl;
	}
	else
	{
		parte_real = -b / (2 * a);
		parte_imaginaria = sqrt(-(b*b - 4 * a * c))/(2*a);
		cout << "This equation has 2 complex roots, with the values: " << parte_real << "+" << parte_imaginaria << "i and " << parte_real << "-" << parte_imaginaria << "i" << endl;
	}
	system("pause");
	return 0;
}