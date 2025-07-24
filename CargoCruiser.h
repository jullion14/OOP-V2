// done by: Lim Jia Herng Julian

// CargoCruiser.h
#ifndef CARGOCRUISER_H
#define CARGOCRUISER_H

#include "Freight.h"

/**
 * @class CargoCruiser
 * @brief A type of Freight with fixed small capacity (6 items).
 *
 * Inherits all standard Freight data (id, location, time).
 * Used for smaller shipments.
 */
class CargoCruiser : public Freight {
public:
    /**
     * @brief Construct a CargoCruiser with given ID, location, and time.
     * @param id  Unique identifier for this vehicle.
     * @param loc Departure or stop code.
     * @param t   Availability time (HHMM).
     */
    CargoCruiser(const std::string& id,
        const std::string& loc,
        time_t             t)
        : Freight(id, loc, t, /*cap=*/6) {
    }

    /// @return Name of this freight type.
    std::string typeName() const override { return "CargoCruiser"; }

    /// @return Maximum load capacity (always 6 for this type).
    size_t maxCapacity() const override { return 6; }
};

#endif // CARGOCRUISER_H
