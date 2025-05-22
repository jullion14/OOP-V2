#pragma once
#include "Freight.h"
#include <vector>

using namespace std;

class FreightStorage :protected Freight
{
protected:
	vector<Freight> freightStorage;

public:
	void loadCargoStorage(string filename, string location, time_t time);
};

