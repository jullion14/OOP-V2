#include "Matcher.h"

Matcher::Matcher() {}

Matcher::Matcher(const Freight& f, const Cargo& c)
    : freight(f), cargo(c) {
}

const Freight& Matcher::getFreight() const {
    return freight;
}

const Cargo& Matcher::getCargo() const {
    return cargo;
}

void Matcher::displayMatch() const {
    std::cout << "Freight: " << freight.getFid()
        << " (" << freight.getFlocation() << ", " << freight.getFtime() << ")"
        << " <--> "
        << "Cargo: " << cargo.getCid()
        << " (" << cargo.getClocation() << ", " << cargo.getCtime() << ")"
        << std::endl;
}
