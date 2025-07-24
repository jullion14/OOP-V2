// done by: Loh Kaize Kaiser

#pragma once

#include "MatchStrategy.h"

/**
 * @class TimeWindowStrategy
 * @brief Matching strategy that pairs freight and cargo by destination and time window.
 *
 * Cargo is eligible for matching only if the freight:
 *   1) Has the same destination,
 *   2) Arrives no later than the cargo time,
 *   3) Arrives no more than windowMins_ minutes before the cargo time.
 */
struct TimeWindowStrategy : MatchStrategy {
    int windowMins_;  ///< Maximum minutes the freight may arrive before cargo time.

    /**
     * @brief Construct a time-window-based matching strategy.
     * @param w Time window in minutes.
     */
    explicit TimeWindowStrategy(int w) : windowMins_(w) {}

    /**
     * @brief Determine if the freight and cargo can match.
     * @param f Freight object.
     * @param c Cargo object.
     * @return True if same destination and time is within the allowed window.
     */
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
