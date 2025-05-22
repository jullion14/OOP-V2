#include "Freight.h"
#include <iostream>

Freight::Freight() : Transport(), Fid(""), Flocation(""), Ftime(0) {}
Freight::Freight(const std::string& id, const std::string& location, time_t time)
    : Transport(id, location, time), Fid(id), Flocation(location), Ftime(time) {
}

std::string Freight::getFid() const { return Fid; }
std::string Freight::getFlocation() const { return Flocation; }
time_t Freight::getFtime() const { return Ftime; }

void Freight::setFid(const std::string& id) { Fid = id; Transport::id = id; }
void Freight::setFlocation(const std::string& location) { Flocation = location; Transport::location = location; }
void Freight::setFtime(time_t time) { Ftime = time; Transport::time = time; }

void Freight::readFreightFile(const std::string& id, const std::string& location, time_t time) {
    Fid = id; Flocation = location; Ftime = time;
    Transport::id = id; Transport::location = location; Transport::time = time;
}

//void Freight::readFile() {
  //  std::cout << "Freight::readFile() called." << std::endl;
//}
