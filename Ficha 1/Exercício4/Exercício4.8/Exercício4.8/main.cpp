#include <iostream>
#include <string>
#include <vector>
using namespace std;

void bubblesort(vector<string> &v)
{
	string temp;
	for (size_t i = 0; i < v.size() - 1; i++)
	{
		for (size_t k = i + 1; k < v.size(); k++)
		{
			if (v[i] > v[k])
			{
				temp = v[i];
				v[i] = v[k];
				v[k] = temp;
			}
		}
	}
}

int main()
{
	string nome;
	vector <string> nomes;
	bool boleano = true;
	while (boleano)
	{
		cout << "\nEnter a name (0 to end): ";
		getline(cin, nome);
		if (nome == "0")
			break;
		else
			nomes.push_back(nome);
	}
	cout << "\nNames by ascending order: \n\n";
	bubblesort(nomes);
	for (size_t j = 0; j < nomes.size(); j++)
		cout << nomes[j] << endl;
	cout << endl;
	system("pause");
	return 0;
}