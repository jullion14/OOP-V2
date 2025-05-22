#pragma once

#include <ctime>
#include "Transport.h"
class Cargo : protected Transport
{
protected:
	string Cid;
	string Clocation;
	time_t Ctime;

public:
	void readCargoFile(string, string, time_t);
};

