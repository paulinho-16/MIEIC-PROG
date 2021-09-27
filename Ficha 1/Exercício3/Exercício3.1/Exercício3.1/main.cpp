#include <iostream>
#include <cmath>
using namespace std;
double distance(double x1, double y1, double x2, double y2)
{
	double distancia;
	distancia = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	return distancia;
}
double area(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double semiperimetro, area_triangulo;
	semiperimetro = (distance(x1, y1, x2, y2) + distance(x2, y2, x3, y3) + distance(x1, y1, x3, y3))/2.0;
	area_triangulo = sqrt(semiperimetro * (semiperimetro - distance(x1, y1, x2, y2)) * (semiperimetro - distance(x2, y2, x3, y3))*(semiperimetro - distance(x1, y1, x3, y3)));
	return area_triangulo;
}
int main()
{
	int x1, y1, x2, y2, x3, y3;
	cout << "Enter the coordinates of the first vertex of the triangle (x y): ";
	cin >> x1 >> y1;
	cout << "Enter the coordinates of the second vertex of the triangle (x y): ";
	cin >> x2 >> y2;
	cout << "Enter the coordinates of the third vertex of the triangle (x y): ";
	cin >> x3 >> y3;
	cout << "The area of the triangle is " << area(x1, y1, x2, y2, x3, y3) << endl;
	system("pause");
	return 0;
}