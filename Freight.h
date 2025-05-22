#pragma once
#include "Transport.h"
class Freight :protected Transport
{
protected:
	string Fid;
	string Flocation;
	time_t Ftime;

public:
	void readFreightFile(string, string, time_t);
};

