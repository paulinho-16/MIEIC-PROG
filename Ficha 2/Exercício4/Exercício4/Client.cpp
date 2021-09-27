#include "Client.h"
using namespace std;

Client::Client()
{
	this->name = "Default";
	this->adress = "Rua Default";
}

Client::Client(string name, string adress)
{
	this->name = name;
	this->adress = adress;
}

string Client::getName()
{
	return this->name;
}

string Client::getAdress()
{
	return this->adress;
}

void Client::setName(string name)
{
	this->name = name;
}

void Client::setAdress(string adress)
{
	this->adress = adress;
}