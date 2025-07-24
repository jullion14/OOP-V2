// done by: Lim Jia Herng Julian

// MegaCarrier.h
#ifndef MEGACARRIER_H
#define MEGACARRIER_H

#include "Freight.h"

/**
 * @class MegaCarrier
 * @brief Freight subtype with fixed medium capacity (12 items).
 *
 * Inherits from Freight and sets the maximum capacity to 12.
 * Used for larger shipments than CargoCruiser, but smaller than MiniMover.
 */
class MegaCarrier : public Freight {
public:
    /**
     * @brief Construct a MegaCarrier.
     * @param id  Unique identifier for the freight.
     * @param loc Departure or location code.
     * @param t   Availability time (HHMM integer format).
     */
    MegaCarrier(const std::string& id,
        const std::string& loc,
        time_t             t)
        : Freight(id, loc, t, /*cap=*/12) {
    }

    /// @return The freight type name ("MegaCarrier").
    std::string typeName() const override { return "MegaCarrier"; }

    /// @return Maximum capacity (always 12 for this type).
    size_t maxCapacity() const override { return 12; }
};

#endif // MEGACARRIER_H
