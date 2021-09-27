#include <iostream>
#include <string>
#include <fstream>
#include "Student.h"
using namespace std;

void showAboveAverageStudents(ofstream &escrever, vector<Student> vetor)
{
	escrever.open("Resultados.txt");
	int soma = 0;
	double media;
	for (size_t i = 0; i < vetor.size(); i++)
		soma += vetor[i].getFinalGrade();
	media = (double)soma / vetor.size();
	for (size_t j = 0; j < vetor.size(); j++)
	{
		if (vetor[j].getFinalGrade() > media)
			escrever << vetor[j].getCode() << '\n' << vetor[j].getName() << '\n' << vetor[j].getShortExam() << '\n' << vetor[j].getProject() << '\n' << vetor[j].getExam() << '\n' << vetor[j].getFinalGrade() << '\n';
	}
	escrever.close();
}

void showAboveAverageStudents(ifstream &ler)
{
	string linha;
	ler.open("Resultados.txt");
	while (getline(ler, linha))
		cout << linha << endl;
	ler.close();
}

int main()
{
	Student estudante1("up201806505","Paulo Ribeiro");
	estudante1.setGrades(18, 17, 17);
	cout << estudante1.getCode() << endl;
	cout << estudante1.getName() << endl;
	cout << estudante1.getFinalGrade() << endl;
	cout << estudante1.isApproved() << endl;
	Student estudante2;
	cout << estudante2.getCode() << endl;
	cout << estudante2.getName() << endl;
	Student estudante3;
	estudante3.readStudentData();
	cout << estudante3.getCode() << endl;
	cout << estudante3.getName() << endl;
	cout << estudante3.getFinalGrade() << endl;
	cout << estudante3.isApproved() << endl;
	cout << "\n----------------------------------------\n";
	bool boleano = true, boleano2 = true;
	char opcao;
	vector<Student> Estudantes;
	while (boleano)
	{
		Student estudante;
		estudante.readStudentData();
		Estudantes.push_back(estudante);
		cin.ignore(1000, '\n');
		boleano2 = true;
		while (boleano2)
		{
			cout << "\nDeseja adicionar um novo estudante? (S/N): ";
			cin >> opcao;
			if (opcao == 'S' || opcao == 's')
				boleano2 = false;
			else if (opcao == 'N' || opcao == 'n')
			{
				boleano = false;
				boleano2 = false;
			}
			else
				cout << "\nOpcao Invalida!\n";
		}
	}
	ofstream escreverficheiro;
	showAboveAverageStudents(escreverficheiro, Estudantes);
	ifstream lerficheiro;
	showAboveAverageStudents(lerficheiro);
	system("pause");
	return 0;
}