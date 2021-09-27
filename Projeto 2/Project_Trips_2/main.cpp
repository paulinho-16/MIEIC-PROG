
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map> 

#include "utils.h"
#include "defs.h"
#include "Agency.h"
#include "Config_and_Stats.h"
#include "Clients_Area.h"
#include "Packs_Management.h"
#include "main.h"

using namespace std;

/**
Loads Main Menu.
*/
int LoadMenu(Agency &agency) 
{
	char opt;

	cout << "\tWelcome to Nice Holidays' Application Menu. Please select an action:" << endl
		<< "\t--------------------------------------------------------------------" << endl
		<< "\t(A) Clients Area" << endl
		<< "\t(B) Packs Management" << endl
		<< "\t(C) Agency Stats" << endl
		<< "\t(D) Configurations" << endl
		<< "\t(E) Credits" << endl
		<< "\t(X) Exit" << endl
		<< "\t-------------------------------" << endl
		<< "\tChoose an action (letter): ";
	cin >> opt;

	switch (opt)
	{
	case 'A':
		system("CLS");
		while (!Manage_Clients(agency));
		Temp_File(agency.getClientsFile(), agency.getClients(), 0, agency, 0);
		break;
	case 'B':
		system("CLS");
		while (!Manage_Packs(agency));
		Temp_File(agency.getPacketsFile(), agency.getPackets(), 0, agency, 1);
		break;
	case 'C':
		system("CLS");
		while(Agency_Stats(agency));
		break;
	case 'D':
		system("CLS");
		while (!Configurations(agency));
		break;
	case 'E':
		system("CLS");
		LoadMotd(0);
		break;
	case 'X':
		Temp_File(AGENCY_FILE_NAME, agency, 1);
		Temp_File(agency.getClientsFile(), agency.getClients(), 1, agency, 0);
		Temp_File(agency.getPacketsFile(), agency.getPackets(), 1, agency, 1);
		return 1;
		break;
	default:
		system("CLS");
		break;
	}
	return 0;
}

/**
Loads Loads Motd Menu and Slogan, or Credits if i is 0.
@param i If 0, Displays credits.
*/
void LoadMotd(int i) 
{
	cout << R"( 
         _   _ _____ _____ ______   _    _  ____  _      _____ _____      __     _______   _     _       
        | \ | |_   _/ ____|  ____| | |  | |/ __ \| |    |_   _|  __ \   /\\ \   / / ____| | |   | |      
        |  \| | | || |    | |__    | |__| | |  | | |      | | | |  | | /  \\ \_/ / (___   | | __| | __ _ 
        | . ` | | || |    |  __|   |  __  | |  | | |      | | | |  | |/ /\ \\   / \___ \  | |/ _` |/ _` |
        | |\  |_| || |____| |____  | |  | | |__| | |____ _| |_| |__| / ____ \| |  ____) | | | (_| | (_| |
        |_| \_|_____\_____|______| |_|  |_|\____/|______|_____|_____/_/    \_\_| |_____/  |_|\__,_|\__,_|
)" << endl << "\t\t\"Wander, Explore, Discover!\"\n" << endl;

	if (i == 0) 
	{
		cout << endl << "\tNice Holidays is a private retailer that provides travel and tourism related" << endl;
		cout << "\tservices to the public on behalf of suppliers such as activities, airlines," << endl;
		cout << "\tcar rentals, cruise lines, hotels, railways, travel insurance, and package tours." << endl;
		cout << endl << "\tPress any key to return to main menu.";
		_getwch();
		system("CLS");
	}

}

/**
Main function - Initiates the program.
*/
int main() 
{
	Agency agency = Agency();

	if (readFiles(agency))
		return 1;
	else
		system("CLS");

	do { LoadMotd(1); } while (!LoadMenu(agency));
	
	cout << "\tThe Program will close. ";

	_getwch();
	return 0;
}