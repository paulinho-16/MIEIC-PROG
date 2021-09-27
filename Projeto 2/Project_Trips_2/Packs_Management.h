#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

#include "Agency.h"
#include "main.h"
#include "Clients_Area.h"
#include "Packs_Management.h"

using namespace std;

void Create_Pack(Agency& agency);
int Change_Pack(Agency& agency);
int Remove_Pack(Agency& agency);
int View_Pack(Agency& agency);
int Manage_Packs(Agency& agency);