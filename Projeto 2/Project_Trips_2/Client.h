#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "defs.h"
#include "Packet.h"
#include "Address.h"

using namespace std;

class Client
{
	private:
		string name; // name of the client
		string VATnumber; // VAT number of client
		unsigned short familySize;  // number of family members
		Address address; // client's address
		string packets; // vector to store client's packets bought
		double totalPurchased; // total value spent by the client
		vector<string> all_props; // vector to store all object's properties as strings

	public:
		static vector<string> props_id; // vector to store the properties' id
		static vector<string> props_default; // vector to store default properties to be read
		Client();
		Client(string name, string VATnumber, unsigned short familySize, Address address);  // for a new client
		Client(string name, string VATnumber, unsigned short familySize, Address address, string packets, double totalPurchased);  // client read from file
	
		// GET methods
		string getName() const;
		string getVATnumber() const;
		unsigned short getFamilySize() const;
		Address getAddress() const;
		string getPacketList() const;
		double getTotalPurchased() const;
		vector<string> getAllProps();

		// SET methods
		void setName(string name);
		void setVATnumber(string VATnumber);
		void setFamilySize(unsigned short familySize);
		void setAddress(Address address);
		void setPacketList(string packets);
		void setTotalPurchased(double totalPurchased);

		// other methods
		vector<Packet> getVectorPackets(vector<Packet> ag_packets);
		bool verify_input(string s, int o) const;
		string NormalizeName(string &name);
		friend ostream &operator<<(ostream &out, Client &client);
		friend ostream &operator<<=(ostream& out, Client &client);

};
