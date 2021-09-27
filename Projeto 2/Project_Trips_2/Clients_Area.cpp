
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "Agency.h"
#include "utils.h"
#include "Clients_Area.h"
#include "Client.h"
#include "Packet.h"

using namespace std;

/**
Instructions to Create a new Client.
@param agency Agency with Vector of Clients to add a new element.
*/
void Create_Client(Agency &agency)
{

	vector<Client> vect = agency.getClients();

	cout << "\n\tCreating a new Client:" 
		 << endl << "\t(Provide the new necessary Info as it follows - write \"_cancel\" to cancel the operation)" << endl;

	Client new_client = Client();

	cin.ignore(1000, '\n');

	vector<string> all_props = new_client.getAllProps();

	for (int i = 0; i < all_props.size() - 2; i++)
	{
		string info;
		do
		{
			Copy_To_ClipBoard(all_props[i]);
			cin.clear();
			cout << '\t' << new_client.props_id[i] << new_client.props_default[i];
			getline(cin, info);
			if (info == "_cancel")
			{
				cout << "\tOperation Canceled. Press any key to return to Clients Area...";
				_getwch();
				system("CLS");
				return;
			}
		} while (cin.fail() || !new_client.verify_input(info, i));
		all_props[i] = info;
	}
	new_client = Client(new_client.NormalizeName(all_props[0]), all_props[1], stoi(all_props[2]), Address(all_props[3]));
	
	vect.push_back(new_client);

	agency.setClients(vect);
	cout << "\tA new client was created. Press any key to return to Clients Area...";

	_getwch();
	system("CLS");
}

/**
Instructions to Buy a pack for a Client.
@param agency Agency with Vector of Clients and Packs.
*/
int Buy_Pack(Agency &agency )
{
	vector<Client> vect_clients = agency.getClients();
	vector<Packet> vect_packs = agency.getPackets();

	bool found = true;
	Client new_client = Client();

	cout << "\n\tChoosing Client:" << endl 
		 << "\t(Provide the necessary Info as it follows)" << endl;
	
	if (vect_clients.size() == 0)
	{
		cout << "\n\tThere are no Clients... Press any key to return to Clients Area.";
		_getwch();
		system("CLS");
		return 1;
	}
	else if (vect_packs.size() == 0) 
	{
		cout << "\n\tThere are no Packs to buy... Press any key to return to Clients Area.";
		_getwch();
		system("CLS");
		return 1;
	}
	cin.ignore(1000, '\n');
	string name;
	
	do
	{
		cin.clear();
		cout << "\tName: ";
		getline(cin, name);

	} while (cin.fail() || name.size() == 0);

	new_client.NormalizeName(name);

	for (int i = 0; i < vect_clients.size(); i++)
	{
		if (vect_clients[i].getName() == name)
		{
			new_client = vect_clients[i];
			found = true;
			vector<string> all_props = new_client.getAllProps();

			cout << "\tClient found. Full Info:\n" << endl;
			cout << new_client;
			cout << "\n\n\tFinding Packs avaiable: " << endl << endl;
			bool pack_found = false;
			for (int i = 0; i < vect_packs.size(); i++)
			{
				if (vect_packs[i].getId() > 0)
				{
					if (vect_packs[i].getCurrentPeople() + new_client.getFamilySize() <= vect_packs[i].getMaxPeople())
					{
						vector<string> all_props_pack = vect_packs[i].getAllProps();
						for (int j = 0; j < vect_packs[i].props_id.size(); j++)
						{
							cout << '\t' << vect_packs[i].props_id[j] << all_props_pack[j] << endl;
						}
						cout << "\t::::::::::" << endl;

						pack_found = true;
					}
				}
			}

			if (!pack_found)
			{
				cout << "\tNo Packs available... Press any key to return to Clients Area.";
				_getwch();
				system("CLS");
				return 1;
			}

			string answ;

			do
			{
				cin.clear();
				cout << "\n\tDo you want to buy any of those? (Yes or No) ";
				getline(cin, answ);

			} while (cin.fail() || answ.size() == 0);

			if (answ == "Yes" || answ == "yes")
			{
				cout << "\tPack id: ";
				int id;
				cin >> id;
				cin.clear();
				int p_found = 0;

				for (int j = 0; j < vect_packs.size(); j++)
				{
					if (vect_packs[j].getId() == id)
					{
						Packet aq_pack = Packet();
						cout << "\tPack info:" << endl << endl;
						p_found = 1;
						aq_pack = vect_packs[j];
						vector<string> all_props_pack = aq_pack.getAllProps();

						for (int k = 0; k < aq_pack.props_id.size(); k++)
						{
							cout << '\t' <<aq_pack.props_id[k] << all_props_pack[k] << endl;
						}

						cin.ignore(1000, '\n');
						Copy_To_ClipBoard(new_client.getVATnumber());
						string nif;
						
						do
						{
							cin.clear();
							cout << "\n\tConfirm your operation: (Your NIF) ";
							getline(cin, nif);

						} while (cin.fail() || nif.size() == 0 || nif != new_client.getVATnumber());

						string p_client = new_client.getPacketList();
						
						if (p_client.size() == 0)
							p_client = to_string(aq_pack.getId());
						else
							p_client += " ; " + to_string(aq_pack.getId());
						
						new_client.setPacketList(p_client);
						new_client.setTotalPurchased(new_client.getTotalPurchased() + aq_pack.getPricePerPerson() * new_client.getFamilySize());
						vect_clients[i] = new_client;

						aq_pack.setCurrentPeople(aq_pack.getCurrentPeople() + new_client.getFamilySize());
						vect_packs[j] = aq_pack;

						agency.setClients(vect_clients);
						agency.setPackets(vect_packs);

						cout << "\tPack aquired. Information was updated. " << endl;
						cout << "\tPress any key to return to Clients Area...";
						_getwch();
						break;
					}
				}
				if (!p_found) 
				{
					cout << "\tNo Packs available... Press any key to return to Clients Area.";
					_getwch();
					system("CLS");
					return 1;
				}

				break;
			}
			else
			{
				cout << "\tNegative or Invalid answer... Press any key to return to Clients Area.";
				_getwch();
				system("CLS");
				return 1;
			}
		}
		else
		{
			found = false;
		}
	}
	if (!found)
	{
		cout << "\tClient not found... Press any key to return to Clients Area.";
		_getwch();
		system("CLS");
		return 1;
	}
	system("CLS");
	return 0;
}

/**
Instructions to Change an existing Client.
@param agency Agency with Vector of Clients to change an element.
*/
int Change_Client(Agency &agency)
{
	vector<Client> vect = agency.getClients();

	bool found = true;
	Client new_client = Client();

	cout << "\n\tChanging Client Info:" << endl
		 << "\t(Provide the new necessary Info as it follows - write \"_cancel\" to cancel the operation)" << endl;
	
	if (vect.size() == 0)
	{
		cout << "\n\tThere are no Clients to change... Press any key to return to Clients Area.";
		_getwch();
		system("CLS");
		return 1;
	}

	cin.ignore(1000, '\n');
	string name;

	do
	{
		cin.clear();
		cout << "\tOriginal Name: ";
		getline(cin, name);

	} while (cin.fail() || name.size() == 0);


	new_client.NormalizeName(name);
	vector<string> all_prps;

	for (int i = 0; i < vect.size(); i++)
	{
		if (vect[i].getName() == name)
		{
			new_client = vect[i];
			cout << "\tProceeding to change Client Info:" << endl;
			vector<string> all_props = new_client.getAllProps();
			Address address = Address();
			for (int i = 0; i < all_props.size(); i++) 
			{
				string info;
				do
				{
					Copy_To_ClipBoard(all_props[i]);
					cin.clear();
					cout << '\t' << new_client.props_id[i] << "( current: " + all_props[i] + " ) ";
					getline(cin, info);
					if (info == "_cancel")
					{
						cout << "\tOperation Canceled. Press any key to return to Clients Area...";
						_getwch();
						system("CLS");
						return 1;
					}
					
				} while (cin.fail() || !new_client.verify_input(info, i));
				
				
				
				if (i == 4)
				{	
					int found_int = 0;
					stringstream ss;
					/* Storing the whole string into string stream */
					ss << info;
					/* Running loop till the end of the stream */
					string temp;
					int exists;
					while (!ss.eof()) {

						/* extracting word by word from stream */
						ss >> temp;

						/* Checking the given word is integer or not */
						if (stringstream(temp) >> exists)
							found_int = 1;
						/* To save from space at the end of string */
						temp = "";
					}

					if(!found_int)
						info = "";
				}
				all_prps.push_back(info);
			}
			new_client = Client(new_client.NormalizeName(all_prps[0]), all_prps[1], stoi(all_prps[2]), Address(all_prps[3]), all_prps[4], stod(all_prps[5]));
			vect[i] = new_client;
			found = true;
			break;
		}
		else
		{
			found = false;
		}
	}
	if (!found)
	{
		cout << "\tClient not found... Press any key to return to Clients Area.";
		_getwch();
		system("CLS");
		return 1;
	}

	agency.setClients(vect);
	cout << "\tAn existing client was changed. Press any key to return to Clients Area...";
	_getwch();
	system("CLS");
	return 0;
}

/**
Instructions to Remove a Client.
@param agency Agency with Vector of Clients to remove the element.
*/
int Remove_Client(Agency &agency)
{
	vector<Client> vect = agency.getClients();
	bool found = true;
	bool answ = true;
	Client new_client;

	cout << "\n\tRemoving Client Info:" << endl 
		 << "\t(Provide the necessary Info as it follows)" << endl;

	if (vect.size() == 0)
	{
		cout << "\n\tThere are no Clients to remove... Press any key to return to Clients Area.";
		_getwch();
		system("CLS");
		return 1;
	}

	
	cin.ignore(1000, '\n');
	string name;

	do
	{
		cin.clear();
		cout << "\tOriginal Name: ";
		getline(cin, name);

	} while (cin.fail() || name.size() == 0);

	new_client.NormalizeName(name);

	for (int i = 0; i < vect.size(); i++)
	{
		if (vect[i].getName() == name)
		{
			new_client = vect[i];
			cout << "\tProceeding to remove Client Info:" << endl;
			
			string anws_s;

			do
			{
				cin.clear();
				cout << "\tAre you sure that you want to remove this client? (Yes or No) ";				
				getline(cin, anws_s);
				
			} while (cin.fail() || anws_s.size() == 0);

			if (anws_s == "Yes" || anws_s == "yes")
			{
				vect.erase(vect.begin() + i);
				found = true;
				break;
			}
			else
			{
				answ = false;
				break;
			}
		}
		else
		{
			found = false;
		}
	}
	if (!answ)
	{
		cout << "\tNegative or Invalid answer. Returning to Configurations...";
		_getwch();
		system("CLS");
		return 1;
	}
	if (!found)
	{
		cout << "\tClient not found... Press any key to return to Clients Area.";
		_getwch();
		system("CLS");
		return 1;
	}
	agency.setClients(vect);
	cout << "\tAn existing client was removed. Press any key to return to Clients Area...";
	_getwch();
	system("CLS");
	return 0;
}

/**
Instructions to View Client's Info.
@param agency Agency with Vector of Clients to search for the elements.
*/
int View_Client(Agency &agency)
{
	bool found = true;
	vector<Client> vect = agency.getClients();
	Client new_client = Client();
	
	cout << "\n\tViewing Clients full Info:" << endl 
		 << "\t(Provide the necessary Info as it follows)" << endl;
	
	if (vect.size() == 0)
	{
		cout << "\n\tThere are no Clients... Press any key to return to Clients Area.";
		_getwch();
		system("CLS");
		return 1;
	}

	cout << "\tWhat type of Information do you want to search? ( All Clients : A ; Specific Client : B ) " 
		 << endl << "\tYour Option: ";
	
	char answ;
	cin >> answ;

	if (answ == 'A')
	{
		cout << endl;
		for (int i = 0; i < vect.size(); i++)
		{
			cout << vect[i];
			cout << "\t::::::::::" << endl;
		}
		cout << "\n\tPress any key to return to Clients Area...";
		_getwch();
		system("CLS");
		return 0;
	}

	if (answ == 'B')
	{
		cin.ignore(1000, '\n');
		string name;

		do
		{
			cin.clear();
			cout << "\tOriginal name: ";
			getline(cin, name);

		} while (cin.fail() || name.size() == 0);

		new_client.NormalizeName(name);
		for (int i = 0; i < vect.size(); i++)
		{
			if (vect[i].getName() == name)
			{
				new_client = vect[i];
				found = true;
				break;
			}
			else
			{
				found = false;
			}
		}
		if (!found)
		{
			cout << "\tClient not found... Press any key to return to Clients Area.";
			_getwch();
			system("CLS");
			return 1;
		}
		else
		{
			cout << "\tClient found. Full Info:\n" << endl;
			cout << new_client;
			cout << "\n\tPress any key to return to Clients Area...";
			_getwch();
			system("CLS");
			return 0;
		}
	}

	cout << "\n\tPress any key to return to Clients Area...";
	_getwch();
	system("CLS");
	return 0;
}

/**
Loads Client's Area Menu.
@param agency Agency.
*/
int Manage_Clients(Agency &agency)
{
	vector<Client> vect_clients = agency.getClients();
	vector<Packet> vect_packs = agency.getPackets();

	cout << R"(
	  ___ _    ___ ___ _  _ _____ ___   _ 
	 / __| |  |_ _| __| \| |_   _/ __| (_)
	| (__| |__ | || _|| .` | | | \__ \  _ 
	 \___|____|___|___|_|\_| |_| |___/ (_)

)";

	for (int i = 0; i < vect_clients.size(); i++)
	{
		cout <<= vect_clients[i];
		cout << "\t::::::::::" << endl;
	}

	char opt;
	cout << "\n\tPlease select an action:" << endl
		<< "\t-------------------------------" << endl
		<< "\t(A) Create Client" << endl
		<< "\t(B) Buy a Pack" << endl
		<< "\t(C) Change Client" << endl
		<< "\t(D) Remove Client" << endl
		<< "\t(E) View Client full Info" << endl
		<< "\t(X) Go to Main Menu" << endl
		<< "\t-------------------------------" << endl
		<< "\tChoose an action (letter): ";
	cin >> opt;
	switch (opt)
	{
		case 'A':
			system("CLS");
			Create_Client(agency);
			break;
		case 'B':
			system("CLS");
			Buy_Pack(agency);
			break;
		case 'C':
			system("CLS");
			Change_Client(agency);
			break;
		case 'D':
			system("CLS");
			Remove_Client(agency);
			break;
		case 'E':
			system("CLS");
			View_Client(agency);
			break;
		case 'X':
			agency.setClients(vect_clients);
			agency.setPackets(vect_packs);
			system("CLS");
			return 1;
			break;
		default:
			system("CLS");
			break;
	}
	return 0;
}