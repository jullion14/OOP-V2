#pragma once
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

class Transport
{
protected:
	string id;
	string location;
	time_t time;
public:
	void readfile();
};

