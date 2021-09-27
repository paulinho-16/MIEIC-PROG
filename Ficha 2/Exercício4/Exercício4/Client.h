#pragma once

#include <string>
using namespace std;

class Client
{
	private:
		string name;
		string adress;
	public:
		Client();
		Client(string name, string adress);
		string getName();
		string getAdress();
		void setName(string name);
		void setAdress(string adress);
};