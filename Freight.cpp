#include "Freight.h"
#include <regex>
#include <stdexcept>

using namespace std;

Freight::Freight() : Transport() {}

Freight::Freight(const string& id, const string& location, time_t time) {
    setFid(id);
    setFlocation(location);
    setFtime(time);
}

string Freight::getFid() const {
    return getId();
}

string Freight::getFlocation() const {
    return getLocation();
}

time_t Freight::getFtime() const {
    return getTime();
}

void Freight::setFid(const string& id) {
    setId(id);
}

void Freight::setFlocation(const string& location) {
   
    if (!regex_match(location, regex("^[A-Za-z ]+$"))) 
    {
        throw invalid_argument("Location must contain only letters and spaces.");
    }
    setLocation(location);
}

void Freight::setFtime(time_t time) {
    if (time < 0 || time > 2359 || time % 100 >= 60) {
        throw invalid_argument("Time must be in 24-hour format (0000 to 2359, valid minutes).");
    }
    setTime(time);
}
