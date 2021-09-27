#include <iostream>
using namespace std;
int main()
{
	float a, b, c, d, e, f, x, y;
	cout << "a ? ";
	cin >> a;
	cout << "b ? ";
	cin >> b;
	cout << "c ? ";
	cin >> c;
	cout << "d ? ";
	cin >> d;
	cout << "e ? ";
	cin >> e;
	cout << "f ? ";
	cin >> f;
	x = (c*e - b*f) / (a*e - b*d);
	y = (a*f - c*d) / (a*e - b*d);
	cout << endl << "x = " << x << endl << "y = " << y << endl;
	_getwch();
	return 0;
}