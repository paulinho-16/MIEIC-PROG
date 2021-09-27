#include <iostream>
using namespace std;
int main()
{
	double operando1, operando2,result;
	char operador;
	cout << "Enter the calculation you want to do (operand1 operator operand2):  ";
	cin >> operando1 >> operador >> operando2;
	switch (operador)
	{
		case '+': result = operando1 + operando2; break;
		case '-': result = operando1 - operando2; break;
		case '*': result = operando1 * operando2; break;
		case '/': result = operando1 / operando2; break;
		default: "Invalid Operation!";
	}
	cout << operando1 << " " << operador << " " << operando2 << " = " << result << endl;
	system("pause");
	return 0;
}