#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

void decompose(string compound)
{
	vector<string> componentes;
	string componente = "";
	for (unsigned int i = 0; i < compound.length(); i++)
	{
		if (isdigit(int(compound[i])))
		{
			componentes.push_back(componente);
			componente = "";
		}
		else if (componente != "" && !islower(compound[i]))
		{
			if (i == compound.length() - 1)
			{
				componentes.push_back(componente);
				componente = compound[i];
				componentes.push_back(componente);
			}
			else
			{
				componentes.push_back(componente);
				componente = compound[i];
			}
		}
		else if (islower(compound[i]))
		{
			componente += compound[i];
			componentes.push_back(componente);
			componente = "";
		}
		else if (i == compound.length() - 1)
		{
			componente += compound[i];
			componentes.push_back(componente);
		}
		else 
			componente += compound[i];
	}	
	cout << "The compounds of " << compound << " are ";
	for (unsigned int j = 0; j < componentes.size(); j++)
	{
		if (j == componentes.size() - 1)
			cout << componentes[j];
		else
			cout << componentes[j] << ", ";
	}
}

int main()
{
	decompose("H2O");
	cout << endl;
	decompose("KOH");
	cout << endl;
	decompose("H2O2");
	cout << endl;
	decompose("NaCl");
	cout << endl;
	decompose("NaOH");
	cout << endl;
	decompose("C9H8O4");
	cout << endl;
	decompose("MgOH");
	cout << endl;
	system("pause");
	return 0;
}