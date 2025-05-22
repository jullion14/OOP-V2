#pragma once

#include "Freight.h"
#include "Cargo.h"
#include <iostream>

class Matcher {
protected:
    Freight freight;
    Cargo cargo;

public:
    Matcher();
    Matcher(const Freight& f, const Cargo& c);

    const Freight& getFreight() const;
    const Cargo& getCargo() const;

    void displayMatch() const;
};
