#include <iostream>
using namespace std;

bool sequenceSearch(string s, int nc, char c)
{
	unsigned int contador = 0,contador_max = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == c)
			contador++;
		else
		{
			if (contador >= contador_max)
				contador_max = contador;
			contador = 0;
		}
	}
	if (contador_max >= nc)
		return true;
	return false;
}

int main()
{
	cout << sequenceSearch("Hello World!", 2, 'l') << endl;
	cout << sequenceSearch("Hello World!", 3, 'l') << endl;
	cout << sequenceSearch("Hello World!", 4, 'o') << endl;
	cout << sequenceSearch("Hello World!", 1, 'd') << endl;
	system("pause");
	return 0;
}