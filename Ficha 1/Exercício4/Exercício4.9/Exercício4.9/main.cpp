#include <iostream>
#include <vector>
using namespace std;

int binarySearch(const vector<string> &v, string value)
{
	int bottom = 0, top = v.size() - 1, middle;
	bool found = false;
	middle = top / 2;
	while (bottom <= top && !found)
	{
		middle = (bottom + top) / 2;
		if (v[middle] == value)
			found = true;
		else
		{
			if (v[middle] < value)
				bottom = middle + 1;
			else
				top = middle - 1;
		}
	}
	if (found)
		return middle;
	return -1;
}

int main()
{
	vector<string> vetor;
	vetor.push_back("America");
	vetor.push_back("Brasil");
	vetor.push_back("Chile");
	vetor.push_back("Dinamarca");
	vetor.push_back("Espanha");
	vetor.push_back("Portugal");
	vetor.push_back("Tunisia");
	cout << binarySearch(vetor, "Espanha") << endl << endl;
	system("pause");
	return 0;
}