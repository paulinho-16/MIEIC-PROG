#include <iostream>
using namespace std;

void readIntArray(int a[], int nElem)
{
	for (int i = 0; i < nElem; i++)
	{
		int numero;
		cout << "Enter an integer number, for the index " << i << ": ";
		cin >> numero;
		a[i] = numero;
	}
}

int searchValueInIntArray(const int a[], int nElem, int value)
{
	for (int j = 0; j < nElem; j++)
	{
		if (a[j] == value)
			return j;
	}
	return -1;
}

int searchMultValuesInIntArray(const int a[], int nElem, int value, int index[])
{
	unsigned int contador = 0;
	for (int k = 0; k < nElem; k++)
	{
		if (a[k] == value)
		{
			index[contador] = k;
			contador++;
		}
	}
	return contador;
}

int main()
{
	int arr[10],valor,indices[10];
	readIntArray(arr, 10);
	cout << "\nEnter the value you want to find: ";
	cin >> valor;
	cout << "\nThe first ocurrence of the value " << valor << " in the array is at index " << searchValueInIntArray(arr, 10, valor) << endl;
	cout << "\nThe " << searchMultValuesInIntArray(arr, 10, valor, indices) << " ocurrences of the value " << valor << " in the array";
	if (searchMultValuesInIntArray(arr, 10, valor, indices) == 0)
	{
		cout << " are at no index" << endl;
		system("pause");
		return 0;
	}
	cout << " are at indexes ";
	for (int l = 0; l < searchMultValuesInIntArray(arr, 10, valor, indices); l++)
	{
		if (l == searchMultValuesInIntArray(arr, 10, valor, indices) - 1)
			cout << indices[l];
		else
			cout << indices[l] << ", ";
	}
	cout << endl;
	system("pause");
	return 0;
}