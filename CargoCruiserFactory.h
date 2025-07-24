// done by: Lim Jia Herng Julian

// CargoCruiserFactory.h
#pragma once

#include "FreightFactory.h"
#include "CargoCruiser.h"
#include <iostream>  // For console output

/**
 * @class CargoCruiserFactory
 * @brief Factory for creating CargoCruiser freight instances.
 *
 * Implements FreightFactory to produce CargoCruiser objects.
 */
struct CargoCruiserFactory : FreightFactory {
    /**
     * @brief Create a CargoCruiser instance.
     * @param id  Unique identifier for the new freight.
     * @param loc Location code.
     * @param t   Availability time (HHMM).
     * @return Shared pointer to a new CargoCruiser.
     */
    std::shared_ptr<Freight>
        create(const std::string& id,
            const std::string& loc,
            time_t             t) const override
    {
        std::cout << "[Factory] Creating CargoCruiser(" << id << ")\n";
        return std::make_shared<CargoCruiser>(id, loc, t);
    }
};
