#include "Transport.h"

Transport::Transport() : id(""), location(""), time(0) {}
Transport::Transport(const std::string& id, const std::string& location, time_t time)
    : id(id), location(location), time(time) {
}
Transport::~Transport() {}

std::string Transport::getId() const { return id; }
std::string Transport::getLocation() const { return location; }
time_t Transport::getTime() const { return time; }

void Transport::setId(const std::string& newId) { id = newId; }
void Transport::setLocation(const std::string& newLocation) { location = newLocation; }
void Transport::setTime(time_t newTime) { time = newTime; }

//void Transport::readFile() {
    // To be overridden in derived classes if needed
//}
