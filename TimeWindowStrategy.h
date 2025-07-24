#pragma once

#include "MatchStrategy.h"

struct TimeWindowStrategy : MatchStrategy {
    int windowMins_;
    explicit TimeWindowStrategy(int w) : windowMins_(w) {}

    bool canMatch(const Freight& f, const Cargo& c) const override {
        // 1) Must be same destination
        if (f.getLocation() != c.getLocation()) {
            return false;
        }

        // 2) Convert HHMM (e.g. 0745) to total minutes since midnight
        auto toMinutes = [](int hhmm) {
            int h = hhmm / 100;
            int m = hhmm % 100;
            return h * 60 + m;
            };

        int fMin = toMinutes(f.getTime());
        int cMin = toMinutes(c.getTime());
        int diff = cMin - fMin;

        // 3) Freight must arrive no later than cargo time (diff ≥ 0)
        //    and no more than windowMins_ minutes early (diff ≤ windowMins_)
        return diff >= 0 && diff <= windowMins_;
    }
};
