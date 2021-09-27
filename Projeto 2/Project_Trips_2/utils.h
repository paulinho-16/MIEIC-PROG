#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map> 

#include <Windows.h>
#include "defs.h"
#include "Agency.h"
#include "Date.h"

using namespace std;

void Temp_File(string FILE_NAME, Agency ag, int updt);

/**
Creates the temp and text files for the clients or packets.
@param FILE_NAME The name of the file to be saved.
@param vect The vector of Clients/Packets.
@param updt If different from 0, txt file is created over tmp file, which is removed.
@param ag The agency.
@param packs If different from 0 writes to packets file the annoying first line - last packet added.
*/
template <class T>
void Temp_File(string FILE_NAME, vector<T> vect, int updt, Agency ag, int packs) 
{
	string FILE_NAME_TEMP;
	size_t n = FILE_NAME.find_last_not_of(".txt");
	for (int i = 0; i <= n; i++) FILE_NAME_TEMP += FILE_NAME[i];
	FILE_NAME_TEMP += ".tmp";
	ofstream file3(FILE_NAME_TEMP);
	if (packs)
		file3 << ag.getLastPacketAdded() << endl;

	for (int i = 0; i < vect.size(); i++) 
	{
		vector<string> v = vect[i].getAllProps();
		for (int j = 0; j < v.size(); j++)
			file3 << v[j] << endl;
		file3 << "::::::::::" << endl;
	}
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
};

void Copy_To_ClipBoard(string source);
int readFiles(Agency& agency);
