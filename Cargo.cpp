#include "Cargo.h"
#include <iostream>

Cargo::Cargo() : Transport(), Cid(""), Clocation(""), Ctime(0) {}
Cargo::Cargo(const std::string& id, const std::string& location, time_t time)
    : Transport(id, location, time), Cid(id), Clocation(location), Ctime(time) {
}

std::string Cargo::getCid() const { return Cid; }
std::string Cargo::getClocation() const { return Clocation; }
time_t Cargo::getCtime() const { return Ctime; }

void Cargo::setCid(const std::string& id) { Cid = id; Transport::id = id; }
void Cargo::setClocation(const std::string& location) { Clocation = location; Transport::location = location; }
void Cargo::setCtime(time_t time) { Ctime = time; Transport::time = time; }

void Cargo::readCargoFile(const std::string& id, const std::string& location, time_t time) {
    Cid = id; Clocation = location; Ctime = time;
    Transport::id = id; Transport::location = location; Transport::time = time;
}

//void Cargo::readFile() {
 //   std::cout << "Cargo::readFile() called." << std::endl;
//}
