#include <iostream>
#include <algorithm>
using namespace std;

struct Fraction
{
	int numerator, denominator;
};

Fraction readFracc()
{
	Fraction Fracao;
	char separator;
	cin >> Fracao.numerator >> separator >> Fracao.denominator;
	if (cin.fail() || separator != '/')
	{
		Fracao.numerator = 0;
		Fracao.denominator = 0;
	}
	return Fracao;
}

void writeFracc(int numerator, int denominator)
{
	cout << numerator << "/" << denominator;
}

Fraction reduceFracc(Fraction f)
{
	int minimo = min(f.numerator, f.denominator);
	int maximo = max(f.numerator, f.denominator);
	int aux;
	while (minimo != 0)
	{
		aux = minimo;
		minimo = maximo % minimo;
		maximo = aux;
	}
	f.numerator /= maximo;
	f.denominator /= maximo;
	return f;
}

Fraction soma(Fraction f1, Fraction f2)
{
	writeFracc(f1.numerator, f1.denominator);
	cout << " + ";
	writeFracc(f2.numerator, f2.denominator);
	cout << " = ";
	f1.numerator *= f2.denominator;
	f2.numerator *= f1.denominator;
	f1.denominator *= f2.denominator;
	int num_final = f1.numerator + f2.numerator;
	Fraction Nova_fracao;
	Nova_fracao.numerator = num_final;
	Nova_fracao.denominator = f1.denominator;
	Nova_fracao = reduceFracc(Nova_fracao);
	return Nova_fracao;
}

Fraction subtracao(Fraction f1,Fraction f2)
{
	writeFracc(f1.numerator, f1.denominator);
	cout << " - ";
	writeFracc(f2.numerator, f2.denominator);
	cout << " = ";
	f1.numerator *= f2.denominator;
	f2.numerator *= f1.denominator;
	f1.denominator *= f2.denominator;
	int num_final = f1.numerator - f2.numerator;
	Fraction Nova_fracao;
	Nova_fracao.numerator = num_final;
	Nova_fracao.denominator = f1.denominator;
	Nova_fracao = reduceFracc(Nova_fracao);
	return Nova_fracao;
}

Fraction multiplicacao(Fraction f1,Fraction f2)
{
	writeFracc(f1.numerator, f1.denominator);
	cout << " * ";
	writeFracc(f2.numerator, f2.denominator);
	cout << " = ";
	int num_final = f1.numerator * f2.numerator;
	int den_final = f1.denominator * f2.denominator;
	Fraction Nova_fracao;
	Nova_fracao.numerator = num_final;
	Nova_fracao.denominator = den_final;
	Nova_fracao = reduceFracc(Nova_fracao);
	return Nova_fracao;
}

Fraction divisao(Fraction f1,Fraction f2)
{
	writeFracc(f1.numerator, f1.denominator);
	cout << " / ";
	writeFracc(f2.numerator, f2.denominator);
	cout << " = ";
	int num_final = f1.numerator * f2.denominator;
	int den_final = f2.numerator * f1.denominator;
	Fraction Nova_fracao;
	Nova_fracao.numerator = num_final;
	Nova_fracao.denominator = den_final;
	Nova_fracao = reduceFracc(Nova_fracao);
	return Nova_fracao;
}

int main()
{
	char operador;
	cout << "Enter a fraction, in the form N/D: ";
	Fraction Fracao;
	Fracao = readFracc();
	cout << Fracao.numerator << " e " << Fracao.denominator << endl;
	writeFracc(Fracao.numerator, Fracao.denominator);
	cout << endl;
	Fracao = reduceFracc(Fracao);
	cout << "Reduced Fraction: " << Fracao.numerator << "/" << Fracao.denominator << endl;
	Fraction Fracao1, Fracao2;
	cout << "Enter the first fraction: ";
	Fracao1 = readFracc();
	cout << "Enter the second fraction: ";
	Fracao2 = readFracc();
	cout << "Enter the operation you want to do (+,-,*,/): ";
	cin >> operador;
	switch (operador)
	{
		case '+':
		{
			Fracao = soma(Fracao1, Fracao2);
			cout << Fracao.numerator << "/" << Fracao.denominator << endl;
			break;
		}
		case '-':
		{
			Fracao = subtracao(Fracao1, Fracao2);
			cout << Fracao.numerator << "/" << Fracao.denominator << endl;
			break;
		}
		case '*':
		{
			Fracao = multiplicacao(Fracao1, Fracao2);
			cout << Fracao.numerator << "/" << Fracao.denominator << endl;
			break;
		}
		case '/':
		{
			Fracao = divisao(Fracao1, Fracao2);
			cout << Fracao.numerator << "/" << Fracao.denominator << endl;
			break;
		}
	}
	system("pause");
	return 0;
}