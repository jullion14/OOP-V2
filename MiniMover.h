// done by: Lim Jia Herng Julian

// MiniMover.h
#ifndef MINIMOVER_H
#define MINIMOVER_H

#include "Freight.h"

/**
 * @class MiniMover
 * @brief Freight subtype with large capacity for bulk cargo.
 *
 * Inherits from Freight and sets the maximum capacity to 50.
 * Used for the largest shipments in the system.
 */
class MiniMover : public Freight {
public:
    /**
     * @brief Construct a MiniMover.
     * @param id  Unique identifier for this freight vehicle.
     * @param loc Departure or stop code.
     * @param t   Availability time (HHMM integer format).
     */
    MiniMover(const std::string& id,
        const std::string& loc,
        time_t             t)
        : Freight(id, loc, t, /* capacity */ 50) {
    }

    /// @return Freight type name ("MiniMover").
    std::string typeName() const override { return "MiniMover"; }

    /// @return Maximum capacity (always 50 for this type).
    size_t maxCapacity() const override { return 50; }
};

#endif // MINIMOVER_H
