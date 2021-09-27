
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "defs.h"
#include "Packet.h"
#include "Address.h"
#include "Client.h"

using namespace std;

vector<string> Client::props_id = // vector to store the properties' id
	{	"Name: ", 
		"NIF: ", 
		"Family Members : " , 
		"Address: ", 
		"Packs aquired: ", 
		"Total Purchased: " 
	}; 

vector<string> Client::props_default =	// vector to store default properties to be read
	{	" (default: Default) ",
		" (default: 123456789) ",
		" (default: 4) " ,
		" (default: street / door / floor / postal / location) ",
		" (default: ) ",
		" (default: 0.0)"	
	}; 

Client::Client()
{
	this->name = "Default";
	this->VATnumber = "123456789";
	this->familySize = 4;
	this->address = Address();
	this->packets = "";
	this->totalPurchased = 0.0;
	
	this->all_props = { 
		this->getName(),
		this->getVATnumber(),
		to_string(this->getFamilySize()),
		this->getAddress().toString(),
		"",
		"0.0"};
};

Client::Client(string name, string VATnumber, unsigned short familySize, Address address) 
{
	this->name = name;
	this->VATnumber = VATnumber;
	this->familySize = familySize;
	this->address = address;
	this->packets = "";
	this->totalPurchased = 0.0;
	
	this->all_props = { 
		this->getName(),
		this->getVATnumber(),
		to_string(this->getFamilySize()),
		this->getAddress().toString(),
		"",
		"0.0"};

};  // for a new client

Client::Client(string name, string VATnumber, unsigned short familySize, Address address, string packets, double totalPurchased) 
{
	this->name = name; 
	this->VATnumber = VATnumber;
	this->familySize = familySize;
	this->address = address;
	this->packets = packets;
	this->totalPurchased = totalPurchased;
	
	this->all_props = { 
		this->getName(),
		this->getVATnumber(),
		to_string(this->getFamilySize()),
		this->getAddress().toString(),
		this->getPacketList(),
		to_string(this->getTotalPurchased()) };

};  // client read from file

// GET methods
string Client::getName() const { return this->name; };
string Client::getVATnumber() const { return this->VATnumber; };
unsigned short Client::getFamilySize() const { return this->familySize; };
Address Client::getAddress() const { return this->address; };
string Client::getPacketList() const { return this->packets; };
double Client::getTotalPurchased() const { return this->totalPurchased; };

vector<string> Client::getAllProps()
{
	this->all_props = {
		this->getName(),
		this->getVATnumber(),
		to_string(this->getFamilySize()),
		this->getAddress().toString(),
		this->getPacketList(),
		to_string(this->getTotalPurchased()) };

	return this->all_props;
};

// SET methods
void Client::setName(string name) { this->name = name; }
void Client::setVATnumber(string VATnumber) { this->VATnumber = VATnumber; };
void Client::setFamilySize(unsigned short familySize) { this->familySize = familySize; };
void Client::setAddress(Address address) { this->address = address; };
void Client::setPacketList(string packets) { this->packets = packets; };
void Client::setTotalPurchased(double totalPurchased) { this->totalPurchased = totalPurchased; };

// other methods
vector<Packet> Client::getVectorPackets(vector<Packet> ag_packets) 
{
	vector<Packet> v;
	string s = this->packets;
	stringstream ss(s);
	string item;
	vector<string> addr;

	while (getline(ss, item, ';'))
	{
		if (item[0] == ' ')
			item.erase(0, 1);
		if (item[item.size() - 1] == ' ')
			item.pop_back();
		addr.push_back(item);
	}

	for (int i = 0; i < addr.size(); i++) 
	{
		for (int j = 0; j < ag_packets.size(); j++) 
		{
			if (abs(ag_packets[j].getId()) == abs(stoi(addr[i])))
				v.push_back(ag_packets[j]);
		}
	}
	return v;
};

/**
Verifies input when managing Client Info.
@return True if everything is ok, False otherwise.*/
bool Client::verify_input(string s, int o) const 
{
	if (s.empty())
		return false;
	if (o == 0)			// Check Name input
	{
		bool isalnm = true;
		for (int j = 0; j < s.length(); j++)
		{
			int c = s[j];
			if ((ispunct(c) && c != int('.')))
				isalnm = false;
		}
		return isalnm;
	}
	else if (o == 1 || o == 2)		// Check NIF and Family size input
	{
		bool isaldgt = true;
		for (int j = 0; j < s.length(); j++)
		{
			int c = s[j];
			if (!isdigit(c))
				isaldgt = false;
		}
		return isaldgt;
	}
	else if (o == 3)		// Check Adress input
	{
		stringstream ss(s);
		string item;
		int counter = 0;
		bool all_ok = true;
		while (getline(ss, item, '/'))
		{
			if (item[0] == ' ')
				item.erase(0, 1);
			if (item[item.size() - 1] == ' ')
				item.pop_back();
			if (counter == 0 || counter == 4)	// Check Street and Location
			{
				for (int j = 0; j < item.length(); j++)
				{
					int c = item[j];
					if (ispunct(c) && c != int('.'))
						all_ok = false;
				}
			}
			else	// Check Door Number, Floor and Postal Code
			{
				for (int j = 0; j < item.length(); j++)
				{
					int c = item[j];
					if (!isdigit(c) && c != int('-'))
						all_ok = false;
				}
			}
			counter++;
		}
		return all_ok;
	}
	return true;
};

string Client::NormalizeName(string &s_name)
{

	if (any_of(begin(s_name), end(s_name), ::isalpha))
	{
		// There is at least one alphabetic character in the string

		s_name = s_name.substr(s_name.find_first_not_of(' '));
		s_name = s_name.substr(0, s_name.find_last_not_of(' ') + 1);
		s_name += " ";
		vector<string> nomes;
		while (s_name.length() != 0)
		{
			s_name.erase(0, s_name.find_first_not_of(' '));
			string nome = s_name.substr(s_name.find_first_not_of(' '), s_name.find_first_of(' ') + 1);
			nome[0] = toupper(nome[0]);
			for (unsigned int j = 1; j < nome.length(); j++)
				nome[j] = tolower(nome[j]);
			nomes.push_back(nome);
			s_name.erase(0, s_name.find_first_of(' ') + 1);
		}
		s_name = "";
		for (unsigned int i = 0; i < nomes.size(); i++)
			s_name += nomes[i];
		s_name = s_name.substr(0, s_name.length() - 1);

	}
	
	return s_name;
};

ostream &operator<<(ostream &out, Client &client)
{
	vector<string> vect = client.getAllProps();
	for (int i = 0; i < vect.size(); i++)
	{
		out << "\t" << client.props_id[i] << vect[i] << "\n";
	}
	return out;
}

ostream& operator<<=(ostream& out, Client &client)
{
	vector<string> v = client.getAllProps();

	for (int i = 0; i < 2; i++) 
	{
		out << "\t" << client.props_id[i] << v[i] << "\n";
	}
	return out;
};