#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "utils.h"
#include "defs.h"
#include "Agency.h"
#include "main.h"

using namespace std;

void Change_Info(Agency& agency);
multimap<int, string, greater<int>> Most_Visited(vector<Packet> v, int updt);
int Clients_Recommended(vector<Packet> v, vector<Client> c);
int Agency_Stats(Agency& agency);
int Configurations(Agency& agency);
