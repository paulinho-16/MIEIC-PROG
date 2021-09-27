#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	double peso,preco;
	cout << "Enter the weight of the merchandise (em gramas): ";
	cin >> peso;
	if (peso < 500)
		preco = 5;
	else if (peso >= 500 && peso <= 1000)
		preco = 5 + ((peso - 500)*1.5) / 100;
	else
		preco = 12.5 + ((peso - 1000) * 5) / 250;
	cout << "The price of the merchandise is: " << fixed << setprecision(2) << preco << " euros" << endl;
	system("pause");
	return 0;
}