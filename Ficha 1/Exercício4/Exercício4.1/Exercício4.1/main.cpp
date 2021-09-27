#include <iostream>
#include <string>
using namespace std;

bool isHydroxideARR(char compound[])
{
	int comprimento = strlen(compound);
	if (compound[comprimento - 2] == 'O' && compound[comprimento - 1] == 'H')
		return true;
	return false;
}

bool isHydroxideSTR(string compound)
{
	int comprimento = compound.length();
	if (compound[comprimento - 2] == 'O' && compound[comprimento - 1] == 'H')
		return true;
	return false;
}

int main()
{
	char koh[] = "KOH";
	cout << isHydroxideARR(koh) << " --- " << isHydroxideSTR("KOH") << endl;
	char h2o2[] = "H2O2";
	cout << isHydroxideARR(h2o2) << " --- " << isHydroxideSTR("H2O2")  << endl;
	char nacl[] = "NaCl";
	cout << isHydroxideARR(nacl) << " --- " << isHydroxideSTR("NaCl") << endl;
	char naoh[] = "NaOH";
	cout << isHydroxideARR(naoh) << " --- " << isHydroxideSTR("NaOH") << endl;
	char c9h8o4[] = "C9H8O4";
	cout << isHydroxideARR(c9h8o4) << " --- " << isHydroxideSTR("C9H8O4") << endl;
	char mgoh[] = "MgOH";
	cout << isHydroxideARR(mgoh) << " --- " << isHydroxideSTR("MgOH") << endl;
	system("pause");
	return 0;
}