#include <iostream>
#include <cmath>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;
int main()
{
	double inicio, fim, step;
	cout << "Enter the desired range (start end): ";
	cin >> inicio >> fim;
	cout << "Enter the desired step between the angles: ";
	cin >> step;
	cout << endl << setw(5) << "    ang         sen          cos          tan" << endl;
	for (double i = inicio; i <= fim; i = i + step)
	{
		cout << setw(9) << fixed << setprecision(6) << i <<  "     " << sin(i*M_PI / 180) << "     " << cos(i*M_PI / 180) << "     ";
		if (tan(i*M_PI / 180) > 9000)
			cout << "infinito" << endl;
		else
			cout << tan(i*M_PI / 180) << endl;
	}
	system("pause");
	return 0;
}