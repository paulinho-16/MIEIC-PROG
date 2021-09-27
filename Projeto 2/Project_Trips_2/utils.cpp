
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map> 
#include <Windows.h>

#include "utils.h"
#include "defs.h"
#include "Agency.h"
#include "Date.h"
#include "Address.h"
#include "Client.h"
#include "Packet.h"

using namespace std;


/**
Copies the string to Clipboard.
@param source The string to copy to Clipboard.
*/
void Copy_To_ClipBoard(string source) 
{
	if (OpenClipboard(NULL))
	{
		HGLOBAL clipbuffer;
		char* buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, source.size() + 1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy_s(buffer, strlen(source.c_str()) + 1, source.c_str());
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT, clipbuffer);
		CloseClipboard();
	}
}

/**
Creates the temp and text files for the agency.
@param FILE_NAME The name of the file to be saved.
@param ag The Agency object.
@param updt If different from 0, txt file is created over tmp file, which is removed.
*/
void Temp_File(string FILE_NAME, Agency ag, int updt) 
{
	string FILE_NAME_TEMP;
	size_t n = FILE_NAME.find_last_not_of(".txt");
	for (int i = 0; i <= n; i++) FILE_NAME_TEMP += FILE_NAME[i];
	FILE_NAME_TEMP += ".tmp";
	ofstream file3(FILE_NAME_TEMP);
	vector<string> v = ag.getAllProps();
	for (int i = 0; i < v.size(); i++)
		file3 << v[i] << endl;
	file3.close();

	if (updt) 
	{
		ifstream file3(FILE_NAME_TEMP);
		ofstream file4;
		file4.open(FILE_NAME, ios::trunc);
		string line2;
		if (file3.good() && file4.good()) 
		{
			while (getline(file3, line2)) 
			{
				file4 << line2 << endl;
			}
		}

		file3.close();
		file4.close();
		remove(FILE_NAME_TEMP.c_str());
	}
}

/**
Reads the files and loads the Agency, Clients and Packets Info.
@return 1 If file read went wrong, returns 1.
*/
int readFiles(Agency &agency) 
{
	cout << R"(
	 _    ___   ___   ___ _  _   _ 
	| |  / _ \ / __| |_ _| \| | (_)
	| |_| (_) | (_ |  | || .` |  _ 
	|____\___/ \___| |___|_|\_| (_)

)";

	cout << "\tAgency file: " << AGENCY_FILE_NAME << endl;
	Copy_To_ClipBoard(AGENCY_FILE_NAME);

	ifstream infile(AGENCY_FILE_NAME);

	if (!infile.good() || infile.peek() == ifstream::traits_type::eof() || infile.peek() == '\0') 
	{
		cout << "\tFailed to read files... Program will close.";
		_getwch();
		return 1;
	}
	else 
	{
		cout << "\t-------------------------------" << endl;
		Address address;
		string line;
		int i = 0;
		vector<string> all_prps;
		while (getline(infile, line)) 
		{
			if (i == 3) 
			{
				stringstream ss(line);
				string item;
				vector<string> addr;
				while (getline(ss, item, '/'))
				{
					if (item[0] == ' ')
						item.erase(0, 1);
					if (item[item.size() - 1] == ' ')
						item.pop_back();
					addr.push_back(item);
				}
				address = Address(addr[0], addr[1], addr[2], addr[3], addr[4]);
			}

			all_prps.push_back(line);
			i++;
		}
		agency.setName(all_prps[0]);
		agency.setVATnumber(all_prps[1]);
		agency.setURL(all_prps[2]);
		agency.setAddress(address);
		agency.setClientsFile(all_prps[4]);
		agency.setPacketsFile(all_prps[5]);
	}
	cout << agency;
	cout << "\t-------------------------------" << endl;
	infile.close();

	ifstream client_file(agency.getClientsFile());
	vector<Client> clients;
	if (!client_file.good()) 
	{
		cout << "\tFailed to read " << agency.getClientsFile() << " file... \n\tProgram will close. ";
		_getwch();
		return 1;
	}
	else if (client_file.peek() == ifstream::traits_type::eof() || client_file.peek() == '\0')
	{

		Client default_client = Client();
		vector<Client> vect = { default_client };
		agency.setClients(vect);

		client_file.close();

	}
	else 
	{
		Address address;
		int i = 0;
		vector<string> all_prps;
		string line;
		while (getline(client_file, line)) 
		{
			if (line.compare("::::::::::")) 
			{
				if (i == 3) 
				{
					stringstream ss(line);
					string item;
					vector<string> addr;
					while (getline(ss, item, '/'))
					{
						if (item[0] == ' ')
							item.erase(0, 1);
						if (item[item.size() - 1] == ' ')
							item.pop_back();
						addr.push_back(item);
					}
					address = Address(addr[0], addr[1], addr[2], addr[3], addr[4]);
				}

				all_prps.push_back(line);
				i++;
			}
			else 
			{

				Client new_client = Client(all_prps[0], all_prps[1], stoi(all_prps[2]), address, all_prps[4], stod(all_prps[5]) );
				i = 0;
				all_prps.clear();
				clients.push_back(new_client);
			}
		}
		client_file.close();
		agency.setClients(clients);
	}
	

	ifstream packs_file(agency.getPacketsFile());
	vector<Packet> packets;
	if (!packs_file.good()) 
	{
		cout << "\tFailed to read " << agency.getPacketsFile() << " file... \n\tProgram will close. ";
		_getwch();
		return 1;
	}
	if (packs_file.peek() == ifstream::traits_type::eof() || packs_file.peek() == '\0' )
	{

		Packet default_packet = Packet();
		default_packet.setId(-9999);
		default_packet.setPricePerPerson(0.0);
		default_packet.setMaxPeople(0);
		vector<Packet> vect = { default_packet };
		agency.setPackets(vect);

		packs_file.close();

	}
	else 
	{
		Date date_b;
		Date date_e;
		int i = 0;
		vector<string> all_prps;
		string line; 
		getline(packs_file, line);
		agency.setLastPacketAdded(stoi(line));

		while (getline(packs_file, line)) 
		{
			if (line.compare("::::::::::")) 
			{
				if (i == 2) 
				{
					stringstream ss(line);
					string item;
					vector<string> addr;
					while (getline(ss, item, '/'))
					{
						if (item[0] == ' ')
							item.erase(0, 1);
						if (item[item.size() - 1] == ' ')
							item.pop_back();
						addr.push_back(item);
					}
					date_b = Date(stoi(addr[0]),stoi(addr[1]), stoi(addr[2]));
				}
				if (i == 3) 
				{
					stringstream ss(line);
					string item;
					vector<string> addr;
					while (getline(ss, item, '/'))
					{
						if (item[0] == ' ')
							item.erase(0, 1);
						if (item[item.size() - 1] == ' ')
							item.pop_back();
						addr.push_back(item);
					}
					date_e = Date(stoi(addr[0]), stoi(addr[1]), stoi(addr[2]));
				}

				all_prps.push_back(line);
				i++;


			}
			else 
			{
				Packet new_pack = Packet(stoi(all_prps[0]), all_prps[1], date_b, date_e, stod(all_prps[4]), stoi(all_prps[5]), stoi(all_prps[6]));
				i = 0;
				all_prps.clear();
				packets.push_back(new_pack);
			}
		}
		packs_file.close();
		agency.setPackets(packets);
	}
	

	cout << "\tAll files were loaded. Press any key to go to Main Menu.";
	_getwch();
	return 0;

}





