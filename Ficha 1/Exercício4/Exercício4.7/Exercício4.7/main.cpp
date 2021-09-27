#include <iostream>
#include <vector>
using namespace std;

void readIntVector(vector<int> &v)
{
	int indice = 0, elemento;
	bool boleano = true;
	while (boleano)
	{
		cout << "Enter the element of index " << indice << ": ";
		cin >> elemento;
		if (cin.fail())
		{
			if (cin.eof())
			{
				boleano = false;
				cin.clear();
			}
			else
			{
				cin.clear();
				cin.ignore(100000, '\n');
			}
			continue;
		}
		v.push_back(elemento);
		indice++;
	}
}

int searchValueInVector(const vector<int> &v, int value)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == value)
			return i;
	}
	return -1;
}

vector<int> searchMultValuesInIntVector(const vector<int> &v, int value)
{
	vector<int> indices;
	for (int j = 0; j < v.size(); j++)
	{
		if (v[j] == value)
			indices.push_back(j);
	}
	return indices;
}

int main()
{
	int valor;
	vector <int> vetor;
	readIntVector(vetor);
	cout << "\nEnter the value you want to find: ";
	cin >> valor;
	if (searchValueInVector(vetor, valor) == -1)
		cout << "\nThe value " << valor << " was not found in the vector." << endl << endl;
	else
	{
		cout << "\nThe first ocurrence of the value " << valor << " in the vector is at index " << searchValueInVector(vetor, valor) << endl;
		cout << "\nThe " << searchMultValuesInIntVector(vetor, valor).size() << " ocurrences of the value " << valor << " are at indexes ";
		for (int k = 0; k < searchMultValuesInIntVector(vetor, valor).size(); k++)
			if (k == searchMultValuesInIntVector(vetor, valor).size() - 1)
				cout << searchMultValuesInIntVector(vetor, valor)[k] << endl << endl;
			else
				cout << searchMultValuesInIntVector(vetor, valor)[k] << ", ";
	}
	system("pause");
	return 0;
}