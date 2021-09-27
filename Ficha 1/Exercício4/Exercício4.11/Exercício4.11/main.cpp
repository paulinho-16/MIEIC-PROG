#include <iostream>
#include <vector>
using namespace std;

void bubblesort(vector<int> &v)
{
	int temp;
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

void removeDuplicates(vector<int> &v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			if (v[i] == v[j])
			{
				for (size_t l = i; l < v.size() - 1; l++)
					v[l] = v[l + 1];
				v.resize(v.size() - 1);
			}
		}
	}
	for (size_t m = 0; m < v.size() - 1; m++)
	{
		if (v[v.size() - 1] == v[m])
			v.resize(v.size() - 1);
	}
}

vector<int> uniao(const vector<int> &v1, const vector<int> &v2)
{
	vector <int> novo_vetor = v1;
	for (size_t i = 0; i < v2.size(); i++)
	{
		novo_vetor.push_back(v2[i]);
	}
	removeDuplicates(novo_vetor);
	bubblesort(novo_vetor);
	return novo_vetor;
}

vector<int> intercecao(const vector<int> &v1, const vector<int> &v2)
{
	vector <int> novo_vetor;
	for (size_t i = 0; i < v1.size(); i++)
	{
		for (size_t j = 0; j < v2.size(); j++)
		{
			if (v1[i] == v2[j])
				novo_vetor.push_back(v1[i]);
		}
	}
	removeDuplicates(novo_vetor);
	bubblesort(novo_vetor);
	return novo_vetor;
}

int main()
{
	vector <int> v1 = { 4,4,6,7,8,8,9,9,10,4,2,1 };
	vector <int> v2 = { 10,11,2,4,5,6,6,7,7,3};
	removeDuplicates(v1);
	removeDuplicates(v2);
	bubblesort(v1);
	bubblesort(v2);
	vector<int> unido = uniao(v1, v2);
	vector<int> intersetado = intercecao(v1, v2);
	cout << "\nVector 1: ";
	for (size_t i = 0; i < v1.size(); i++)
		cout << v1[i] << " ";
	cout << "\nVector 2: ";
	for (size_t i = 0; i < v2.size(); i++)
		cout << v2[i] << " ";
	cout << "\nVector after reunion: ";
	for (size_t i = 0; i < unido.size(); i++)
		cout << unido[i] << " ";
	cout << "\nVector after intersection: ";
	for (size_t i = 0; i < intersetado.size(); i++)
		cout << intersetado[i] << " ";
	cout << endl;
	system("pause");
	return 0;
}