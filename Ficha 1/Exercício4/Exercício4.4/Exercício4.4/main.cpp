#include <iostream>
#include <string>
#include <vector>

using namespace std;

string normalizeName(string name)
{
	name = name.substr(name.find_first_not_of(' '));
	name = name.substr(0,name.find_last_not_of(' ')+1);
	name += " ";
	vector<string> nomes;
	while (name.length() != 0)
	{
		name.erase(0, name.find_first_not_of(' '));
		string nome = name.substr(name.find_first_not_of(' '), name.find_first_of(' ') + 1);
		nome[0] = toupper(nome[0]);
		for (unsigned int j = 1; j < nome.length(); j++)
			nome[j] = tolower(nome[j]);
		nomes.push_back(nome);
		name.erase(0, name.find_first_of(' ') + 1);
	}
	name = "";
	for (unsigned int i = 0; i < nomes.size(); i++)
		name += nomes[i];
	name = name.substr(0, name.length() - 1);
	string preposicoes[6] = { "De ", "Do ", "Da ","Das ","Dos "," e " };
	for (unsigned int k = 0; k < 6; k++)
	{
		if (name.find(preposicoes[k]) != string::npos)
		{
			if (k == 5)
			{
				name.insert(name.find(preposicoes[k]), " ");
				name.erase(name.find(preposicoes[k]), preposicoes[k].length());
			}
			else
				name.erase(name.find(preposicoes[k]), preposicoes[k].length());
		}
	}
	return name;
}

int main()
{
	string name;
	cout << "Enter your full name: ";
	getline(cin, name);
	cout << "Normalized name: " << normalizeName(name) <<  endl;
	system("pause");
	return 0;
}