#pragma once
#include "Cargo.h"
#include <vector>

class CargoStorage : protected Cargo
{
protected:
	vector<Cargo> cargoStorage;
public:
	void loadCargoStorage(string filename, string location, time_t time);
};

