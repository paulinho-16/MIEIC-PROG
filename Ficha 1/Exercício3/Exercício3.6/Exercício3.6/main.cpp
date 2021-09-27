#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

bool Bissexto(int ano)
{
	if (ano % 400 == 0)
		return true;
	else if (ano % 4 == 0 && ano % 100 != 0)
		return true;
	return false;
}

int Dias_Mes(int mes, int ano)
{
	if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
		return 30;
	else if (mes == 2)
	{
		if (Bissexto(ano))
			return 29;
		return 28;
	}
	else
		return 31;
}

int Dia_Semana(int ano, int mes, int dia)
{
	int copia = ano, digitos = 0,c;
	while (copia != 0)
	{
		copia /= 10;
		digitos++;
	}
	int ultimos_2 = ano % int((pow(10, digitos - 2)));
	int primeiros_2 = int(ano / pow(10, digitos - 2));
	switch (mes)
	{
		case 1:
		{
			if (Bissexto(ano))
				c = 6;
			else
				c = 0;
			break;
		}
		case 2:
		{
			if (Bissexto(ano))
				c = 2;
			else
				c = 3;
			break;
		}
		case 3:
			c = 3; break;
		case 4:
			c = 6; break;
		case 5:
			c = 1; break;
		case 6:
			c = 4; break;
		case 7:
			c = 6; break;
		case 8:
			c = 2; break;
		case 9:
			c = 5; break;
		case 10:
			c = 0; break;
		case 11:
			c = 3; break;
		case 12:
			c = 5; break;
	}
	int ds = int(floor(5 * ultimos_2 / 4.0) + c + dia - 2 * (primeiros_2 % 4) + 7) % 7;
	return ds;
}

void Calendario_Mes(int mes, int ano)
{
	switch (mes)
	{
		case 1:
			cout << "Janeiro" << "/" << ano; break;
		case 2:
			cout << "Fevereiro" << "/" << ano; break;
		case 3:
			cout << "Marco" << "/" << ano; break;
		case 4:
			cout << "Abril" << "/" << ano; break;
		case 5:
			cout << "Maio" << "/" << ano; break;
		case 6:
			cout << "Junho" << "/" << ano; break;
		case 7:
			cout << "Julho" << "/" << ano; break;
		case 8:
			cout << "Agosto" << "/" << ano; break;
		case 9:
			cout << "Setembro" << "/" << ano; break;
		case 10:
			cout << "Outubro" << "/" << ano; break;
		case 11:
			cout << "Novembro" << "/" << ano; break;
		case 12:
			cout << "Dezembro" << "/" << ano; break;
	}
	cout << endl << "Dom" << '\t' << "Seg" << '\t' << "Ter" << '\t' << "Qua" << '\t' << "Qui" << '\t' << "Sex" << '\t' << "Sab" << endl;
	int primeiro_dia = Dia_Semana(ano, mes, 1);
	if (primeiro_dia == 0)
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << setw(3) << 1 << endl;
	else
	{
		for (int j = 0; j < primeiro_dia - 1; j++)
			cout << '\t';
		cout << setw(3) << 1;
	}

	for (int i = 2; i <= Dias_Mes(mes, ano); i++)
	{
		if (Dia_Semana(ano, mes, i) == 0)
			cout << '\t' << setw(3) << i << endl;
		else if (Dia_Semana(ano, mes, i) == 1)
			cout << setw(3) << i;
		else
			cout << '\t' << setw(3) << i;
	}
	cout << endl;
}

int main()
{
	int dia, mes, ano;
	string nome_dia;
	cout << "Enter a date (with numbers, day month year): ";
	cin >> dia >> mes >> ano;
	cout << endl;
	switch (Dia_Semana(ano, mes, dia))
	{
		case 0:
			nome_dia = "Sabado"; break;
		case 1:
			nome_dia = "Domingo"; break;
		case 2:
			nome_dia = "Segunda"; break;
		case 3:
			nome_dia = "Terca"; break;
		case 4:
			nome_dia = "Quarta"; break;
		case 5:
			nome_dia = "Quinta"; break;
		case 6:
			nome_dia = "Sexta"; break;
	}
	cout << dia << "/" << mes << "/" << ano << " is " << nome_dia << "." << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "Enter a month and an year (month year): ";
	cin >> mes >> ano;
	cout << endl;
	Calendario_Mes(mes, ano);
	char opcao;
	cout << endl << endl << "Do you want to see the calendar of an entire year? (S or N): ";
	cin >> opcao;
	if (opcao == 'N' || opcao == 'n')
	{
		system("pause");
		return 0;
	}
	cout << "Enter an year: ";
	cin >> ano;
	cout << endl;
	for (int k = 1; k <= 12; k++)
	{
		Calendario_Mes(k, ano);
		cout << endl;
	}
	system("pause");
	return 0;
}