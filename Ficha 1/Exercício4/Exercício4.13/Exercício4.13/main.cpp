#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void ordenar(vector<string> &vetor)
{
	sort(vetor.begin(), vetor.end());
}

int main()
{
	vector<string> nomes;
	string nome, linha;
	cout << "Introduza o nome do ficheiro de texto (sem a extensao txt): ";
	cin >> nome;
	ifstream ler_ficheiro;
	ler_ficheiro.open(nome + ".txt");
	while (getline(ler_ficheiro, linha))
		nomes.push_back(linha);
	ler_ficheiro.close();
	ordenar(nomes);
	ofstream escrever_ficheiro;
	escrever_ficheiro.open(nome + "_sorted.txt");
	for (size_t i = 0; i < nomes.size(); i++)
		escrever_ficheiro << nomes[i] << endl;
	escrever_ficheiro.close();
	system("pause");
	return 0;
}