#include <iostream>
#include <string>
using namespace std;
int main()
{
	int n , i = 2;
	cout << "Enter an integer number: ";
	cin >> n;
	string result = to_string(n) + "=";
	while (n != 1)
	{
		while (n % i == 0)
		{
			result += to_string(i) + "x";
			n /= i;
		}
		if (n == 1)
			break;
		i++;
	}
	result.pop_back();
	cout << result << endl;
	system("pause");
	return 0;
}