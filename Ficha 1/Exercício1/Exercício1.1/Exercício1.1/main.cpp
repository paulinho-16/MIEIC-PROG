#include <iostream>
using namespace std;
int main()
{
	char letra;
	cout << "Enter a letter: ";
	cin >> letra;
	cout << "The ascii code for " << letra << " is " << hex << int(letra) << "." << endl;
	_getwch();
	return 0;
}