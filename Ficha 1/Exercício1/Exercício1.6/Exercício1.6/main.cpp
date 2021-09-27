#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int x1, y1, x2, y2, x3, y3;
	float lado1, lado2, lado3, semiperimetro,area;
	cout << "Enter the coordinates of the first triangle vertex (x y): ";
	cin >> x1 >> y1;
	cout << "Enter the coordinates of the second triangle vertex (x y): ";
	cin >> x2 >> y2;
	cout << "Enter the coordinates of the third triangle vertex (x y): ";
	cin >> x3 >> y3;
	lado1 = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	lado2 = sqrt(pow(x3 - x1, 2) + pow(y3 - y1, 2));
	lado3 = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
	semiperimetro = (lado1 + lado2 + lado3) / 2;
	area = sqrt(semiperimetro*(semiperimetro - lado1)*(semiperimetro - lado2)*(semiperimetro - lado3));
	cout << "The area of the triangle is " << area <<  endl;
	_getwch();
	return 0;
}