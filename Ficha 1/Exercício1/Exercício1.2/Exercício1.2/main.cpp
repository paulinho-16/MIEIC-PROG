#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	int A, B, C;
	float media, dA, dB, dC;
	cout << "A ? ";
	cin >> A;
	cout << "B ? ";
	cin >> B;
	cout << "C ? ";
	cin >> C;
	media = (A + B + C) / 3.0;
	dA = A - media;
	dB = B - media;
	dC = C - media;
	cout << "media = " << fixed << setprecision(3) << media << endl;
	cout << "A-media = " << fixed << setprecision(3) << dA << endl;
	cout << "B-media = " << fixed << setprecision(3) << dB << endl;
	cout << "C-media = " << fixed << setprecision(3) << dC << endl;
	_getwch();
	return 0;
}