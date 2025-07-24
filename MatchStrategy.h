// done by: Loh Kaize Kaiser

#pragma once

#include "Freight.h"
#include "Cargo.h"

/**
 * @brief Abstract interface for matching strategy.
 *
 * Provides a way to determine if a specific Freight can carry a specific Cargo.
 * Used to implement different matching rules (e.g., time windows, locations, etc).
 */
struct MatchStrategy {
    /**
     * @brief Determine if the freight and cargo match according to some rule.
     * @param f The Freight to check.
     * @param c The Cargo to check.
     * @return true if they match according to this strategy; false otherwise.
     */
    virtual bool canMatch(const Freight& f, const Cargo& c) const = 0;

    /// Virtual destructor for interface cleanup.
    virtual ~MatchStrategy() = default;
};
