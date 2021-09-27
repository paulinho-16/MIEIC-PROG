
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map> 
#include <iterator>
#include <algorithm>

#include "utils.h"
#include "defs.h"
#include "Agency.h"
#include "main.h"
#include "Config_and_Stats.h"

using namespace std;

/**
Instructions to change Agency Info.
*/
void Change_Info(Agency &agency) 
{
	cout << "\n\tChanging the Agency Info:" << endl 
		 << "\t(Provide the new necessary Info as it follows - write \"_cancel\" to cancel the operation)\n" << endl;

	cin.ignore(1000, '\n');
	string line;
	Address address;
	vector<string> user_input;

	for (int i = 0; i < agency.props_id.size(); i++) 
	{
		do 
		{
			cin.clear();
			cout << '\t' << agency.props_id[i] << agency.props_default[i];
			Copy_To_ClipBoard(agency.getAllProps()[i]);
			getline(cin, line);

			if (line == "_cancel") 
			{
				cout << endl << "\tOperation Canceled. Press any key to return to Configurations...";
				_getwch();
				system("CLS");
				return;
			};

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
			user_input.push_back(line);
		} while (cin.fail() || !agency.verify_input(line, i));
	}
	
	agency.setName(user_input[0]);
	agency.setVATnumber(user_input[1]);
	agency.setURL(user_input[2]);
	agency.setAddress(address);
	agency.setClientsFile(user_input[4]);
	agency.setPacketsFile(user_input[5]);

	Temp_File(AGENCY_FILE_NAME, agency, 0);
	cout << endl << "\tInfo has changed. Press any key to return to Configurations...";
	_getwch();
	system("CLS");

}

template<typename A, typename B>
pair<B, A> flip_pair(const pair<A, B>& p)
{
	return pair<B, A>(p.second, p.first);
}

template<typename A, typename B>
multimap<B, A, greater<B>> flip_map(const map<A, B>& src)
{
	multimap<B, A, greater<B>> dst;
	transform(src.begin(), src.end(), inserter(dst, dst.begin()),
		flip_pair<A, B>);
	return dst;
}

/**
First N most visited sites
@param v Vector of Packets
@param updt If 1, returns automatically to Stats menu
*/
multimap<int, string, greater<int>> Most_Visited(vector<Packet> v, int updt) 
{
	map<string, int> mp;

	for (int i = 0; i < v.size(); i++) 
	{
		vector<string> sites = v[i].spec_sites();
		for (int j = 0; j < sites.size(); j++) 
		{

			string s = sites[j];
			mp[s] += v[i].getCurrentPeople();
		}
	}
	
	cout << endl << endl << "\tMost Visited Sites: " << endl;
	int opt = 0; 
	cin.clear();
	cin.ignore(1000, '\n');
	size_t limit = mp.size();
	while (opt > limit || opt < 1 || cin.fail()) 
	{
		cout << "\tHow many places to display (Between 1 and "<< limit << "): ";
		cin >> opt;
		if (cin.fail()) 
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
	
	multimap<int, string, greater<int>> dst = flip_map(mp);
	int n = 0;

	cout << endl << "\t##-\t\tSite (Packet):\tVisits:" << endl;
	cout << "\t---------------------------------------" << endl;
	for(auto mi = dst.begin(); mi != dst.end(); mi++)
	{
		n++; 
		if(n<10) cout << '\t' << n << " - " << setw(26) << mi->second << setw(9) << mi->first << endl;
		else  cout << '\t' << n << "- " << setw(26) << mi->second << setw(9) << mi->first << endl;
		if (n == opt) 
		{
			dst.erase(++mi, dst.end());
			break;
		}
	}
	if (updt) 
	{ 
		cout << endl << "\tPress enter to return to the stats...";	
		_getwch(); 
	}

	return dst;
}

/**
Clients Recommended Sites
@param v Vector of Packets
@param c Vector of Clients
*/
int Clients_Recommended(vector<Packet> v, vector<Client> clients) 
{
	multimap<int, string, greater<int>> dst = Most_Visited(v,0);

	cout << endl << endl << "\tRecommendations for Clients: " << endl << endl;

	cout << "\tClient:\t\t\t\tNIF:\t\tRecommendation (Packet):" << endl;
	cout << "\t------------------------------------------------------------------------" << endl;
	
	for (int c = 0; c < clients.size(); c++) 
	{
		
		vector<Packet> visited = clients[c].getVectorPackets(v);
		
		//Packs Not Visited
		vector<Packet> not_visited;
		for (int i = 0; i < v.size(); i++) 
		{
			int found = 0;
			for (int j = 0; j < visited.size(); j++) 
			{
				if (abs(visited[j].getId()) == abs(v[i].getId()))
				{
					found = 1;
					break;
				}
			}
			if (!found)
				not_visited.push_back(v[i]);
		}
		
				
		//All sites not visited
		vector<string> sites;
		for (int j = 0; j < not_visited.size(); j++) 
		{
			vector<string> v_packets = not_visited[j].spec_sites();
			sites.insert(sites.end(), v_packets.begin(), v_packets.end());

		}
		
		vector<string> recommended_sites;
		vector<string> v_same;

		//All sites visited
		for (int i = 0; i < visited.size(); i++)
		{
			vector<string> v_packets = visited[i].spec_sites();
			v_same.insert(v_same.end(), v_packets.begin(), v_packets.end());

		}

		//All recommended not yet visited
		for (int i = 0; i < sites.size(); i++)
		{
			int found = 0;
			for (int j = 0; j < v_same.size(); j++)
			{
				if (v_same[j] == sites[i])
				{
					found = 1;
					break;
				}
			}
			if (!found)
				recommended_sites.push_back(sites[i]);
		}
		
		int id_recommended = 0;
		// The client recomendation

		for (auto mi = dst.begin(); mi != dst.end(); mi++)
		{
			int found = 0;

			for(int i = 0; i < recommended_sites.size(); i++)
			{
				if(recommended_sites[i] == mi->second)
				{
					for (int j = 0; j < not_visited.size(); j++)
					{
						vector<string> pack_sites = not_visited[j].spec_sites();

						if (find(pack_sites.begin(), pack_sites.end(), recommended_sites[i]) != pack_sites.end()) {
							if(not_visited[j].getCurrentPeople() + clients[c].getFamilySize() <= not_visited[j].getMaxPeople() && not_visited[j].getId() > 0)
							{
								found = 1;
								id_recommended = not_visited[j].getId();
								break;			
						
							}
						}
					}			
				}

				if (found) break;
			
			}
			
			if (found) break;

		}

		cout << "\t";
		cout.width(25); cout << left << clients[c].getName();
		cout << setw(11) << right << clients[c].getVATnumber();
		
		if (id_recommended <= 0)
		{
			cout << setw(36) << "Not Found" << endl; 
			continue;
	
		}
		else
		{
			cout << setw(36) << id_recommended << endl;
			continue;
		}

	}
	cout << endl << "\tPress enter to return to the stats...";
	_getwch();
	return 1;
}

/**
Displays Agency Stats.
*/
int Agency_Stats(Agency& agency) {

	cout << R"(
	   _   ___ ___ _  _  _____   __  ___ _____ _ _____ ___   _ 
	  /_\ / __| __| \| |/ __\ \ / / / __|_   _/_\_   _/ __| (_)
	 / _ \ (_ | _|| .` | (__ \ V /  \__ \ | |/ _ \| | \__ \  _ 
	/_/ \_\___|___|_|\_|\___| |_|   |___/ |_/_/ \_\_| |___/ (_)

)";

	cout << "\tOverview:" << endl << endl;

	vector<Packet> packs = agency.getPackets();

	double total_c = 0.0, total_e = 0.0;

	cout << "\tPack ID:\tCount Sold:\tPrice (Per Person):\tEarnings:" << endl;
	cout << "\t-----------------------------------------------------------------------------" << endl;

	for (int i = 0; i < packs.size(); i++) 
	{
		total_c += packs[i].getCurrentPeople();
		total_e += packs[i].getPricePerPerson() * double(packs[i].getCurrentPeople());
		cout << '\t' << setw(8) << packs[i].getId() 
			<< setw(19) << packs[i].getCurrentPeople() 
			<< fixed << setprecision(2)
			<< setw(24) << packs[i].getPricePerPerson() 
			<< setw(14) << packs[i].getPricePerPerson() * double(packs[i].getCurrentPeople()) << endl;
	}

	cout << "\t-----------------------------------------------------------------------------" << endl;
	cout << "\tTotal:" << setw(21) << int(total_c) << setw(38) << fixed << setprecision(2) << total_e << endl << endl;
	   
	char opt;

	cout << "\tOther Stats:" << endl
		<< "\t-------------------------------" << endl
		<< "\t(A) Most Visited Sites" << endl
		<< "\t(B) Clients Recommended Sites" << endl
		<< "\t(X) Go to Main Menu" << endl
		<< "\t-------------------------------" << endl
		<< "\tChoose an action (letter): ";
	cin >> opt;

	switch (opt)
	{
	case 'A':
		Most_Visited(packs,1);
		system("CLS");
		return 1;
		break;
	case 'B':
		Clients_Recommended(packs, agency.getClients());
		system("CLS");
		return 1;
		break;
	case 'X':
		cout << endl << "\tPress any key to return to Main Menu...";
		_getwch();
		system("CLS");
		return 0;
		break;
	default:
		system("CLS");
		return 1;
		break;
	}

}

/**
Loads Configurations Menu.
*/
int Configurations(Agency& agency) {
	
	cout << R"(
	  ___ ___  _  _ ___ ___ ___ _   _ ___    _ _____ ___ ___  _  _ ___   _ 
	 / __/ _ \| \| | __|_ _/ __| | | | _ \  /_\_   _|_ _/ _ \| \| / __| (_)
	| (_| (_) | .` | _| | | (_ | |_| |   / / _ \| |  | | (_) | .` \__ \  _ 
	 \___\___/|_|\_|_| |___\___|\___/|_|_\/_/ \_\_| |___\___/|_|\_|___/ (_)

)";
	
	cout << agency;

	char opt;

	cout << "\n\tPlease select an action:" << endl
		<< "\t-------------------------------" << endl
		<< "\t(A) Change Info" << endl
		<< "\t(X) Go to Main Menu" << endl
		<< "\t-------------------------------" << endl
		<< "\tChoose an action (letter): ";

	cin >> opt;
	switch (opt)
	{
	case 'A':
		system("CLS");
		Change_Info(agency);
		break;
	case 'X':
		system("CLS");
		return 1;
		break;
	default:
		system("CLS");
		break;
	}

	return 0;
}

