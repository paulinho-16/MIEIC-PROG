#include <iostream>
#include <algorithm>
using namespace std;
char separator;
int numerator = 0, denominator = 0;

bool readFracc(int &numerator, int &denominator)
{
	cin >> numerator >> separator >> denominator;
	if (cin.fail() || separator != '/')
	{
		numerator = 0;
		denominator = 0;
		return false;
	}
	else
		return true;
}

void writeFracc(int numerator, int denominator)
{
	cout << numerator << "/" << denominator;
}

void reduceFracc(int &numerator, int &denominator)
{	
	int minimo = min(numerator, denominator);
	int maximo = max(numerator, denominator);
	int aux;
	while (minimo != 0) 
	{
		aux = minimo;
		minimo = maximo % minimo;
		maximo = aux;
	}
	numerator /= maximo;
	denominator /= maximo;
	cout << numerator << "/" << denominator;
}

void soma(int num1, int den1, int num2, int den2)
{
	writeFracc(num1, den1);
	cout << " + ";
	writeFracc(num2, den2);
	cout << " = ";
	num1 *= den2;
	num2 *= den1;
	den1 *= den2;
	int num_final = num1 + num2;
	reduceFracc(num_final, den1);
	cout << endl;
}

void subtracao(int num1, int den1, int num2, int den2)
{
	writeFracc(num1, den1);
	cout << " - ";
	writeFracc(num2, den2);
	cout << " = ";
	num1 *= den2;
	num2 *= den1;
	den1 *= den2;
	int num_final = num1 - num2;
	reduceFracc(num_final, den1);
	cout << endl;
}

void multiplicacao(int num1, int den1, int num2, int den2)
{
	writeFracc(num1, den1);
	cout << " * ";
	writeFracc(num2, den2);
	cout << " = ";
	int num_final = num1 * num2;
	int den_final = den1 * den2;
	reduceFracc(num_final, den_final);
	cout << endl;
}

void divisao(int num1, int den1, int num2, int den2)
{
	writeFracc(num1, den1);
	cout << " / ";
	writeFracc(num2, den2);
	cout << " = ";
	int num_final = num1 * den2;
	int den_final = num2 * den1;
	reduceFracc(num_final, den_final);
	cout << endl;
}

int main()
{
	char operador;
	int numerador1, denominador1, numerador2, denominador2;
	cout << "Enter a fraction, in the form N/D: ";
	cout << readFracc(numerator, denominator) << endl;
	writeFracc(numerator, denominator);
	cout << endl;
	reduceFracc(numerator, denominator);
	cout << endl;
	cout << "     -------------------      " << endl;
	cout << "Enter the first fraction, in the form N/D: ";
	readFracc(numerador1, denominador1);
	cout << "Enter the second fraction, in the form N/D: ";
	readFracc(numerador2, denominador2);
	cout << "Enter the operation you want to do (+,-,*,/): ";
	cin >> operador;
	switch (operador)
	{
		case '+':
			soma(numerador1, denominador1, numerador2, denominador2); break;
		case '-':
			subtracao(numerador1, denominador1, numerador2, denominador2); break;
		case '*':
			multiplicacao(numerador1, denominador1, numerador2, denominador2); break;
		case '/':
			divisao(numerador1, denominador1, numerador2, denominador2); break;
	}
	system("pause");
	return 0;
}