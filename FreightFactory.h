// done by: Lim Jia Herng Julian

// FreightFactory.h
#ifndef FREIGHTFACTORY_H
#define FREIGHTFACTORY_H

#include <memory>
#include "Freight.h"

/**
 * @brief Abstract factory interface for creating Freight objects.
 *
 * Used to support polymorphic construction of different Freight subtypes.
 */
struct FreightFactory {
    virtual ~FreightFactory() = default;

    /**
     * @brief Create a Freight instance (subtype).
     * @param id   Unique identifier for the freight.
     * @param loc  Location code.
     * @param t    Availability time in HHMM format.
     * @return Shared pointer to the created Freight.
     */
    virtual std::shared_ptr<Freight>
        create(const std::string& id,
            const std::string& loc,
            time_t             t) const = 0;
};

#endif // FREIGHTFACTORY_H
