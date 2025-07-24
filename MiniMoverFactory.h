// done by: Lim Jia Herng Julian

// MiniMoverFactory.h
#pragma once

#include "FreightFactory.h"
#include "MiniMover.h"
#include <iostream>  // For console output

/**
 * @class MiniMoverFactory
 * @brief Factory for creating MiniMover freight instances.
 *
 * Implements FreightFactory to produce MiniMover objects with a given ID, location, and time.
 */
struct MiniMoverFactory : FreightFactory {
    /**
     * @brief Create a MiniMover freight.
     * @param id  Unique identifier for the freight.
     * @param loc Departure location code.
     * @param t   Availability time (HHMM format).
     * @return Shared pointer to a new MiniMover.
     */
    std::shared_ptr<Freight>
        create(const std::string& id,
            const std::string& loc,
            time_t             t) const override
    {
        std::cout << "[Factory] Creating MiniMover(" << id << ")\n";
        return std::make_shared<MiniMover>(id, loc, t);
    }
};
