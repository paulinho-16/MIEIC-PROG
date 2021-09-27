#include <iostream>
#include <string> 
#include <sstream>
using namespace std;

double executeOperation(string op)
{
	double operando1, operando2;
	char operador;
	istringstream extrair(op);
	extrair >> operando1 >> operador >> operando2;
	switch (operador)
	{
		case '+':
			return operando1 + operando2; 
			break;
		case '-':
			return operando1 - operando2;
			break;
		case '*':
			return operando1 * operando2;
			break;
		case '/':
			return operando1 / operando2;
			break;
	}
}

int main()
{
	cout << executeOperation("12.3 + 5") << endl;
	cout << executeOperation("7 - 2.3") << endl;
	cout <<	executeOperation("5 * 6") << endl;
	cout << executeOperation("17 / 5") << endl;
	system("pause");
	return 0;
}