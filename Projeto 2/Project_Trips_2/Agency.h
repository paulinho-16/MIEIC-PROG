#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "defs.h"
#include "Address.h"
#include "Client.h"
#include "Packet.h"

using namespace std;

class Agency
{
	private:
		string name; // name of the  agency
		string VATnumber; // VAT number of the agency
		string URL; // URL of the agency Web site
		Address address; // address of the agency
		string clients_file; // clients file name
		string packets_file; // packets file name
		vector<Client> clients; // vector to store the existing clients
		vector<Packet> packets; // vector to store the existing packets
		int lastPacketAdded;
		vector<string> all_props; // vector to store all object's properties as strings

	public:
		static vector<string> props_id; // vector to store the properties' id
		static vector<string> props_default; // vector to store default properties to be read

		Agency();

		// methods GET
		string getName() const;
		string getVATnumber() const;
		string getURL() const;
		Address getAddress() const;
		string getClientsFile() const;
		string getPacketsFile() const;
		vector<Client> getClients() const;
		vector<Packet> getPackets() const;
		int getLastPacketAdded() const; 
		vector<string> getAllProps();

		// methods SET
		void setName(string name);
		void setVATnumber(string VATnumber);
		void setURL(string url);
		void setAddress(Address address);
		void setClientsFile(string file_name);
		void setPacketsFile(string file_name);
		void setClients(vector<Client>& clients);
		void setPackets(vector<Packet>& packets);
		void setLastPacketAdded(int packet);

		// other methods
		friend ostream& operator<<(ostream& out, Agency& agency);
		bool verify_input(string s, int o) const;
};
