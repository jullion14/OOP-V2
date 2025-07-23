#pragma once

#include "MatchStrategy.h"
#include <cstdlib>  // for std::abs()

struct TimeWindowStrategy : MatchStrategy {
    int windowMins_;
    explicit TimeWindowStrategy(int w) : windowMins_(w) {}

    bool canMatch(const Freight& f, const Cargo& c) const override {
        return f.getLocation() == c.getLocation()
            && std::abs(int(f.getTime()) - int(c.getTime())) <= windowMins_;
    }
};

