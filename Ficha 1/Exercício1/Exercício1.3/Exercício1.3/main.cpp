#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
using namespace std;
int main()
{
	float p, r, M;
	cout << "Enter the density, in Kg/m^3: ";
	cin >> p;
	cout << "Enter the radius, in m: ";
	cin >> r;
	M = (4 / 3)*(p*M_PI*pow(r, 3));
	cout << "The mass of sphere is : " << M << " Kg" << endl;
	_getwch();
	return 0;
}