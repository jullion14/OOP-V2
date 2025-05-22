#include "Cargo.h"
#include <regex>
#include <stdexcept>

Cargo::Cargo() : Transport() {}

Cargo::Cargo(const std::string& id, const std::string& location, time_t time) {
    setCid(id);
    setClocation(location);
    setCtime(time);
}

std::string Cargo::getCid() const {
    return getId();  
}

std::string Cargo::getClocation() const {
    return getLocation();  
}

time_t Cargo::getCtime() const {
    return getTime();  
}

void Cargo::setCid(const std::string& id) {
    setId(id);  
}

void Cargo::setClocation(const std::string& location) {
    if (!std::regex_match(location, std::regex("^[A-Za-z ]+$"))) {
        throw std::invalid_argument("Location must contain only letters and spaces.");
    }
    setLocation(location);  
}

void Cargo::setCtime(time_t time) {
    if (time < 0 || time > 2359 || time % 100 >= 60) {
        throw std::invalid_argument("Time must be in 24-hour format (0000 to 2359, valid minutes).");
    }
    setTime(time);  
}
