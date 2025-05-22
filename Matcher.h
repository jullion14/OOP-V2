#pragma once

#include "Freight.h"
#include "Cargo.h"

class Matcher {
protected:
    Freight matchedFreight;
    Cargo matchedCargo;

public:
    Matcher();
    Matcher(const Freight& freight, const Cargo& cargo);

    Freight getFreight() const;
    Cargo getCargo() const;

    void setFreight(const Freight& freight);
    void setCargo(const Cargo& cargo);

    void displayMatch() const;
};
