#ifndef MEGACARRIER_H
#define MEGACARRIER_H

#include "Freight.h"

class MegaCarrier : public Freight {
public:
    MegaCarrier(const std::string& id,
        const std::string& loc,
        time_t             t)
        : Freight(id, loc, t, /*cap=*/12)
    {
    }
    size_t maxCapacity() const override { return 12; }
};

#endif // MEGACARRIER_H
