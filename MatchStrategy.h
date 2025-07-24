// done by: Loh Kaize Kaiser


#pragma once

#include "Freight.h"
#include "Cargo.h"

struct MatchStrategy {
    virtual bool canMatch(const Freight& f, const Cargo& c) const = 0;
    virtual ~MatchStrategy() = default;
};
