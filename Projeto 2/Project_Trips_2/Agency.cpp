
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Agency.h"
#include "defs.h"
#include "Address.h"
#include "Client.h"
#include "Packet.h"

using namespace std;

vector<string> Agency::props_id = // vector to store the properties' id
	{ 
		"Name: ", 
		"NIF: ", 
		"Url: " , 
		"Address: ", 
		"Clients file: ", 
		"Packs file: " 
	}; 

vector<string> Agency::props_default = // vector to store default properties to be read
	{	" (default: Nice Holidays lda) ",
		" (default: 123456789) ",
		" (default: www.niceholidays.com) " ,
		" (default: street / door / floor / postal / location) ",
		" (default: clients.txt) ",
		" (default: packs.txt) " 
	};  

Agency::Agency() {
	this->name = "Nice Holidays lda";
	this->VATnumber = "123456789";
	this->URL = "www.niceholidays.com";
	this->address = Address("street", "door", "floor", "postal", "location");
	this->clients_file = "clients.txt";
	this->packets_file = "packs.txt";
	this->lastPacketAdded = 0;

	this->all_props = { this->getName(),
		this->getVATnumber(), 
		this->getURL(), 
		this->getAddress().toString(), 
		this->getClientsFile(), 
		this->getPacketsFile() };
};

// methods GET
string Agency::getName() const {
	return this->name;
};
string Agency::getVATnumber() const {
	return this->VATnumber;
};
string Agency::getURL() const {
	return this->URL;
};
Address Agency::getAddress() const {
	return this->address;
};
string Agency::getClientsFile() const {
	return this->clients_file;
};
string Agency::getPacketsFile() const {
	return this->packets_file;
};
vector<Client> Agency::getClients() const {
	return this->clients;
};
vector<Packet> Agency::getPackets() const {
	return this->packets;
};
int Agency::getLastPacketAdded() const {
	return this->lastPacketAdded;
};
vector<string> Agency::getAllProps() {
	this->all_props = { this->getName(),
		this->getVATnumber(),
		this->getURL(),
		this->getAddress().toString(),
		this->getClientsFile(),
		this->getPacketsFile() };
	return this->all_props;
};

// methods SET
void  Agency::setName(string name) { this->name = name; };
void  Agency::setVATnumber(string VATnumber) { this->VATnumber = VATnumber; };
void  Agency::setURL(string url) { this->URL = url; };
void  Agency::setAddress(Address address) { this->address = address; };
void  Agency::setClientsFile(string file_name) { this->clients_file = file_name; };
void  Agency::setPacketsFile(string file_name) { this->packets_file = file_name; };
void  Agency::setClients(vector<Client>& clients) { this->clients = clients; };
void  Agency::setPackets(vector<Packet>& packets) { this->packets = packets; };
void  Agency::setLastPacketAdded(int packet) { this->lastPacketAdded = packet; };

// other methods
ostream& operator<<(ostream& out, Agency& agency) 
{
	vector<string> v = agency.getAllProps();

	for (int i = 0; i < v.size(); i++) {
	out << "\t" << agency.props_id[i] << v[i] << "\n";
	}
	return out;
};

/**
Verifies input when changing Agency info.
@return True if everything is ok, False otherwise.*/
bool Agency::verify_input(string s, int o) const{
	if (s.empty())
		return false;
	if (o == 0 || o == 2) // Check Name and URL input
	{
		bool isalnm = true;
		for (int j = 0; j < s.length(); j++) {
			int c = s[j];
			if (ispunct(c) && c != int('.'))
				isalnm = false;
		}
		return isalnm;
	}
	else if (o == 1) // Check VAT number input
	{
		bool isaldgt = true;
		for (int j = 0; j < s.length(); j++) {
			int c = s[j];
			if (!isdigit(c))
				isaldgt = false;
		}
		return isaldgt;
	}
	else if (o == 3) // Check Address input
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
			if (counter == 0 || counter == 4) {

				for (int j = 0; j < item.length(); j++) {
					int c = item[j];
					if (ispunct(c) && c != int('.'))
						all_ok = false;
				}
			}
			else {
				for (int j = 0; j < item.length(); j++) {
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

