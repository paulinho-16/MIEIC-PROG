#include <iostream>
#include <vector>
using namespace std;

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
	for (size_t m = 0; m < v.size()-1; m++)
	{
		if (v[v.size() - 1] == v[m])
			v.resize(v.size() - 1);
	}
}

int main()
{
	vector <int> v = { 1,2,3,1,3,4,5,5,6,7,5,6,8,9,8,8,8,8};
	removeDuplicates(v);
	cout << "With no repeated elements:\n";
	for (size_t k = 0; k < v.size(); k++)
	{
		cout << v[k] << endl;
	}
	system("pause");
	return 0;
}