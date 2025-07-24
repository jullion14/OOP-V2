// done by: Lim Jia Herng Julian

// MegaCarrierFactory.h
#pragma once

#include "FreightFactory.h"
#include "MegaCarrier.h"
#include <iostream>  // For console output

/**
 * @class MegaCarrierFactory
 * @brief Factory for creating MegaCarrier freight instances.
 *
 * Implements the FreightFactory interface to produce
 * MegaCarrier objects with a specified ID, location, and timestamp.
 */
struct MegaCarrierFactory : FreightFactory {
    /**
     * @brief Create a MegaCarrier.
     * @param id  Unique identifier for the freight.
     * @param loc Departure location code.
     * @param t   Availability time in HHMM format.
     * @return Shared pointer to the new MegaCarrier.
     */
    std::shared_ptr<Freight>
        create(const std::string& id,
            const std::string& loc,
            time_t             t) const override
    {
        std::cout << "[Factory] Creating MegaCarrier(" << id << ")\n";
        return std::make_shared<MegaCarrier>(id, loc, t);
    }
};
