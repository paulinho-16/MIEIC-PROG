#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main()
{
	double n, delta, rq = 1, rqn, rqn2, dif, copia;
	int nMaxIter , iteracoes = 0, decimais = 0;
	cout << "Enter a number to calculate his square root: ";
	cin >> n;
	cout << "Enter the minimum variation for the program to stop: ";
	cin >> delta;
	dif = delta + 1;
	cout << "Enter the maximum number of iterations for the program to stop: ";
	cin >> nMaxIter;
	while ((abs(dif) > delta) && (iteracoes <= nMaxIter))
	{
		iteracoes++;
		rqn = (rq + n / rq) / 2;
		rqn2 = pow(rqn, 2);
		dif = n - rqn2;
		rq = rqn;
	}
	copia = delta;
	copia = copia - round(copia);
	while (copia >= 0.00000000000001)
	{
		copia *= 10;
		decimais++;
		copia = copia - round(copia);
	}
	cout << "The square root of the number " << n << " is " << fixed << setprecision(decimais) << rq << endl;
	cout << "The square root of this number in the C library is " << sqrt(n) << endl;
	system("pause");
	return 0;
}