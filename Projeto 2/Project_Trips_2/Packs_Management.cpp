
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

#include "Agency.h"
#include "main.h"
#include "utils.h"
#include "Clients_Area.h"
#include "Packs_Management.h"

using namespace std;

/**
Instructions to Create a new Package.
@param agency Agency with Vector of Packages to add a new element.
*/
void Create_Pack(Agency &agency) 
{
	cout << "\n\tCreating a new Pack:" << endl << "\t(Provide the new necessary Info as it follows - write \"_cancel\" to cancel the operation)" << endl;

	Packet new_pack = Packet();

	cin.ignore(1000, '\n');
	vector<string> all_props = new_pack.getAllProps();

	cout << '\t' << new_pack.props_id[0] << abs(agency.getLastPacketAdded()) + 1 << endl;

	for (int i = 1; i < all_props.size() - 1; i++) 
	{
		string info;

		do 
		{
			Copy_To_ClipBoard(all_props[i]);
			cin.clear();
			cout << '\t' << new_pack.props_id[i] << new_pack.props_default[i];
			getline(cin, info);
			if (info == "_cancel") 
			{
				cout << "\tOperation Canceled. Press any key to return to Pack Management...";
				_getwch();
				system("CLS");
				return;
			}
		} while (cin.fail() || !new_pack.verify_input(info, i));
		all_props[i] = info;
	}

	new_pack = Packet(
		abs(agency.getLastPacketAdded()) + 1,
		all_props[1], 
		Date(all_props[2]), 
		Date(all_props[3]), 
		stod(all_props[4]),
		stoi(all_props[5]),
		stoi(all_props[6]));
	
	vector<Packet> vect = agency.getPackets();
	vect.push_back(new_pack);
	agency.setPackets(vect);
	agency.setLastPacketAdded(new_pack.getId());

	cout << "\tA new pack was created. Press any key to return to Pack Management...";
	_getwch();
	system("CLS");
}


/**
Instructions to Change an existing Package.
@param agency Agency with Vector of Packages to change an element.
*/
int Change_Pack(Agency& agency) 
{
	vector<Packet> vect = agency.getPackets();

	bool found = true;
	Packet new_pack = Packet();
	
	cout << "\n\tChanging Pack Info:" << endl << "\t(Provide the new necessary Info as it follows - write \"_cancel\" to cancel the operation)" << endl;
	
	if (vect.size() == 0) 
	{
		cout << "\n\tThere are no Packs to change... Press any key to return to Packs Management.";
		_getwch();
		system("CLS");
		return 1;
	}
	int id;
	do{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "\tOriginal id: ";
		cin >> id;
		
	} while (cin.fail());

	cin.ignore(1000, '\n');
	vector<string> all_props;

	for (int i = 0; i < vect.size(); i++) 
	{
		if (vect[i].getId() == id) 
		{
			new_pack = vect[i];
			cout << "\tProceeding to change Pack Info:" << endl;
			cout << '\t' << new_pack.props_id[0] << id << endl;
			all_props.push_back(to_string(id));
			for (int i = 1; i < new_pack.getAllProps().size(); i++) 
			{
				string info;
				do 
				{
					Copy_To_ClipBoard(new_pack.getAllProps()[i]);
					cin.clear();
					cout << '\t' << new_pack.props_id[i] << "( current: " + new_pack.getAllProps()[i] + " ) ";
					getline(cin, info);
					if (info == "_cancel") 
					{
						cout << "\tOperation Canceled. Press any key to return to Pack Management...";
						_getwch();
						system("CLS");
						return 1;
					}

				} while (cin.fail() || !new_pack.verify_input(info, i));
				all_props.push_back(info);
			}
			new_pack = Packet(
				stoi(all_props[0]),
				all_props[1],
				Date(all_props[2]),
				Date(all_props[3]),
				stod(all_props[4]),
				stoi(all_props[5]),
				stoi(all_props[6]));

			vect[i] = new_pack;
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
		cout << "\tPack not found... Press any key to return to Packs Management.";
		_getwch();
		system("CLS");
		return 1;
	}
	agency.setPackets(vect);
	cout << "\tAn existing pack was changed. Press any key to return to Packs Management...";
	_getwch();
	system("CLS");
	return 0;
}


/**
Instructions to Remove a Package.
@param agency Agency with Vector of Packages to remove the element.
*/
int Remove_Pack(Agency& agency) 
{
	vector<Packet> vect = agency.getPackets();

	bool found = true;
	bool answ = true;
	Packet new_pack = Packet();

	cout << "\n\tRemoving Pack Info:" << endl 
		 << "\t(Provide the necessary Info as it follows)" << endl;

	if (vect.size() == 0) 
	{
		cout << "\n\tThere are no Packs to remove... Press any key to return to Packs Management.";
		_getwch();
		system("CLS");
		return 1;
	}

	int id;

	do 
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "\tOriginal id: ";
		cin >> id;

	} while (cin.fail());

	cin.ignore(1000, '\n');
	
	if (id <= 0)
	{
		cout << "\tNegative Ids cannot be removed. Returning to Packs Management...";
		_getwch();
		system("CLS");
		return 1;
	}

	for (int i = 0; i < vect.size(); i++) 
	{
		if (vect[i].getId() == id) 
		{
			new_pack = vect[i];
			cout << "\tProceeding to remove Pack Info:" << endl;
			cout << "\tAre you sure that you want to remove this pack? (Yes or No) ";
			string anws_s;
			getline(cin, anws_s);
			if (anws_s == "Yes" || anws_s == "yes") 
			{
				new_pack.setId(-1 * new_pack.getId());
				vect[i]= new_pack;
				found = true;
				break;

			}
			else {
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
		cout << "\tNegative or Invalid answer. Returning to Packs Management...";
		_getwch();
		system("CLS");
		return 1;
	}
	if (!found) 
	{

		cout << "\tPack not found... Press any key to return to Packs Management.";
		_getwch();
		system("CLS");
		return 1;

	}
	agency.setPackets(vect);
	cout << "\tAn existing Pack was removed. Press any key to return to Packs Management...";
	_getwch();
	system("CLS");
	return 0;
}

/**
Instructions to View Package's Info.
@param agency Agency with Vector of Packages to search for the elements.
*/
int View_Pack(Agency& agency) 
{
	vector<Packet> vect = agency.getPackets();

	bool found = false;

	cout << "\n\tViewing Packs ( Available - Positive and Unavailable - Negative Packs ) full Info:" << endl 
		 << "\t(Provide the necessary Info as it follows)" << endl;
	
	if (vect.size() == 0)
	{
		cout << "\n\tThere are no Packs... Press any key to return to Packs Management.";
		_getwch();
		system("CLS");
		return 1;
	}

	cout << "\tWhat type of Information do you want to search? ( All Packs : A ; Specific Packs : B ) " << endl 
		 << "\tYour Option: ";

	char answ;
	cin >> answ;

	// Print Every Packet Info.

	if (answ == 'A') 
	{

		cout << endl;

		for (int i = 0; i < vect.size(); i++) 
		{
			cout << vect[i];
			cout << "\t::::::::::" << endl;
		}
		cout << "\n\tPress any key to return to Packs Management...";
		_getwch();
		system("CLS");
		return 0;
	}

	// Print Info of a Chosen Packet 

	if (answ == 'B') 
	{
		cout << "\tSearch for:" << endl;
		char opt;
		cout << "\t-------------------------------" << endl
			<< "\t(A) Id" << endl
			<< "\t(B) Places" << endl
			<< "\t(C) Between Dates" << endl
			<< "\t(D) Places and Dates" << endl
			<< "\t-------------------------------" << endl
			<< "\tChoose an action (letter): ";
		cin >> opt;

		string places, date_b, date_e;
		Date dateBegin = Date();
		Date dateEnd = Date();
		vector<Packet> vect_search;

		switch (opt)
		{
		case 'A':

			cin.ignore(1000, '\n');

			int id;
			do 
			{
				cin.clear();
				cout << "\tId: ";
				cin >> id;

			} while (cin.fail());
			for (int i = 0; i < vect.size(); i++) 
			{
				if (vect[i].getId() == id) 
				{
					vect_search.push_back(vect[i]);
					found = true;
				}
			}
			break;
		case 'B':
			
			cin.ignore(1000, '\n');

			do
			{
				cin.clear();
				cout << "\tPlaces: ";
				getline(cin, places);

			} while (cin.fail() || places.size() == 0);

			for (int i = 0; i < vect.size(); i++) 
			{
				if (vect[i].getSites().find(places) != string::npos) 
				{
					vect_search.push_back(vect[i]);
					found = true;
				}
			}
			break;
		case 'C':
			
			cin.ignore(1000, '\n');

			do 
			{
				cin.clear();
				cout << "\tBeginning Date (year/month/day): ";
				getline(cin, date_b);
			} while (cin.fail() || !dateBegin.verify_input(date_b) || date_b.size() == 0);
			
			do 
			{
				cin.clear();
				cout << "\tEnding Date (year/month/day): ";
				getline(cin, date_e);
			} while (cin.fail() || !dateEnd.verify_input(date_e) || date_e.size() == 0);

			dateBegin = Date(date_b);
			dateEnd = Date(date_e);

			for (int i = 0; i < vect.size(); i++) 
			{
				if (vect[i].getBeginDate() >= dateBegin && vect[i].getEndDate() <= dateEnd) 
				{
					vect_search.push_back(vect[i]);
					found = true;
				}
			}
			break;
		case 'D':
			cin.ignore(1000, '\n');

			do
			{
				cin.clear();
				cout << "\tPlaces: ";
				getline(cin, places);

			} while (cin.fail() || places.size() == 0);


			do
			{
				cin.clear();
				cout << "\tBeginning Date (year/month/day): ";
				getline(cin, date_b);
			} while (cin.fail() || !dateBegin.verify_input(date_b) || date_b.size() == 0);

			do
			{
				cin.clear();
				cout << "\tEnding Date (year/month/day): ";
				getline(cin, date_e);
			} while (cin.fail() || !dateEnd.verify_input(date_e) || date_e.size() == 0);



			dateBegin = Date(date_b);
			dateEnd = Date(date_e);

			for (int i = 0; i < vect.size(); i++) 
			{
				if (vect[i].getBeginDate() >= dateBegin && vect[i].getEndDate() <= dateEnd && vect[i].getSites().find(places) != string::npos) 
				{
					vect_search.push_back(vect[i]);
					found = true;
				}
			}
			break;
		default:
			cout << "\n\tPress any key to return to Packs Management...";
			_getwch();
			system("CLS");
			return 0;
			break;
		}

		if (!found) 
		{
			cout << "\tPack(s) not found... Press any key to return to Packs Management.";
			_getwch();
			system("CLS");
			return 1;
		}
		else 
		{
			cout << "\tPack(s) found. Full Info:\n" << endl;
			for (int j = 0; j < vect_search.size(); j++) 
			{
				Packet new_pack = vect_search[j];
				cout << vect_search[j];
				cout << "\t::::::::::" << endl;
			}
			cout << "\n\tPress any key to return to Packs Management...";
			_getwch();
			system("CLS");
			return 0;
		}
	}
	cout << "\n\tPress any key to return to Packs Management...";
	_getwch();
	system("CLS");
	return 0;
}


/**
Loads Package's Management Menu.
@param agency Agency with Vector of Packages.
*/
int Manage_Packs(Agency &agency)
{
	vector<Packet> vect_packs = agency.getPackets();

	cout << R"(
	 ___  _   ___ _  _____   _ 
	| _ \/_\ / __| |/ / __| (_)
	|  _/ _ \ (__| ' <\__ \  _ 
	|_|/_/ \_\___|_|\_\___/ (_)

)";

	for (int i = 0; i < vect_packs.size(); i++) 
	{
		cout <<= vect_packs[i];
		cout << "\t::::::::::" << endl;
	}

	char opt;

	cout << "\n\tPlease select an action:" << endl
		<< "\t-------------------------------" << endl
		<< "\t(A) Create Pack" << endl
		<< "\t(B) Change Pack" << endl
		<< "\t(C) Remove Pack" << endl
		<< "\t(D) View Pack full Info" << endl
		<< "\t(X) Go to Main Menu" << endl
		<< "\t-------------------------------" << endl
		<< "\tChoose an action (letter): ";
	cin >> opt;

	switch (opt)
	{
	case 'A':
		system("CLS");
		Create_Pack(agency);
		break;
	case 'B':
		system("CLS");
		Change_Pack(agency);
		break;
	case 'C':
		system("CLS");
		Remove_Pack(agency);
		break;
	case 'D':
		system("CLS");
		View_Pack(agency);
		break;
	case 'X':
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

