#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
	cout << time(NULL);
	int operador1,operador2,resposta,result;
	double tempo_inicial;
	srand(time(NULL));
	tempo_inicial = time(NULL);
	operador1 = rand() % 8 + 2;
	operador2 = rand() % 8 + 2;
	cout << operador1 << " x " << operador2 << " = ";
	cin >> resposta;
	result = operador1 * operador2;
	if (resposta != result)
		cout << "Muito Mau - Answer time: " << time(NULL) - tempo_inicial << "s" << endl;
	else if (time(NULL) - tempo_inicial < 5)
		cout << "Bom - Answer time: " << time(NULL) - tempo_inicial << "s" << endl;
	else if (time(NULL) - tempo_inicial >= 5 && time(NULL) - tempo_inicial <= 10)
		cout << "Satisfaz - Answer time: " << time(NULL) - tempo_inicial << "s" << endl;
	else
		cout << "Insuficiente - Answer time: " << time(NULL) - tempo_inicial << "s" << endl;
	system("pause");
	return 0;
}