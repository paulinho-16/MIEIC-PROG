#include <iostream>
using namespace std;
int main()
{
	int h1, m1, s1, h2, m2, s2,segundos,minutos,horas,dias,minutos_sobra,horas_sobra;
	cout << "Tempo 1 (horas minutos segundos) ? ";
	cin >> h1 >> m1 >> s1;
	cout << "Tempo 2 (horas minutos segundos) ? ";
	cin >> h2 >> m2 >> s2;
	segundos = (s1 + s2) % 60;
	minutos_sobra = (s1 + s2 - segundos) / 60;
	minutos = (m1 + m2 + minutos_sobra) % 60;
	horas_sobra = (m1 + m2 + minutos_sobra - minutos) / 60;
	horas = (h1 + h2 + horas_sobra) % 24;
	dias = (h1 + h2 + horas_sobra - horas) / 24;
	cout << "Soma dos tempos: " << dias << " dia, " << horas << " horas, " << minutos << " minutos e " << segundos << " segundos" << endl;
	_getwch();
	return 0;
}