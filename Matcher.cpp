#include "Matcher.h"
#include <iostream>

Matcher::Matcher()
    : matchedFreight(), matchedCargo() {
}

Matcher::Matcher(const Freight& freight, const Cargo& cargo)
    : matchedFreight(freight), matchedCargo(cargo) {
}

Freight Matcher::getFreight() const {
    return matchedFreight;
}

Cargo Matcher::getCargo() const {
    return matchedCargo;
}

void Matcher::setFreight(const Freight& freight) {
    matchedFreight = freight;
}

void Matcher::setCargo(const Cargo& cargo) {
    matchedCargo = cargo;
}

void Matcher::displayMatch() const {
    std::cout << "Matched Freight: " << matchedFreight.getFid()
        << " (" << matchedFreight.getFlocation() << ", " << matchedFreight.getFtime() << ")"
        << " <--> "
        << "Cargo: " << matchedCargo.getCid()
        << " (" << matchedCargo.getClocation() << ", " << matchedCargo.getCtime() << ")"
        << std::endl;
}
