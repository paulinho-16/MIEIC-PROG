#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int numero,copia,digitos = 2,primeiro_digito,ultimo_digito;
	cout << "Enter an integer number: ";
	cin >> numero;
	copia = numero;
	while (digitos > 1)
	{
		int nova_copia = copia;
		digitos = 0;
		while (nova_copia != 0) // Achar numero de digitos
		{
			nova_copia = int(nova_copia / 10);
			digitos += 1;
		}
		if (digitos == 0)
			break;
		primeiro_digito = int(copia / pow(10, digitos - 1));
		ultimo_digito = copia % 10;
		if (primeiro_digito == ultimo_digito)
		{
			copia = copia % int(pow(10, digitos - 1));
			copia = int(copia / 10);
		}
		else
		{
			cout << "The number " << numero << " is not a palindrome." << endl;
			system("pause");
			return 0;
		}
	}
	cout << "The number " << numero << " is a palindrome." << endl;
	system("pause");
	return 0;
}