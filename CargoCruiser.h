#ifndef CARGOCRUISER_H
#define CARGOCRUISER_H

#include "Freight.h"

class CargoCruiser : public Freight {
public:
    CargoCruiser(const std::string& id,
        const std::string& loc,
        time_t             t)
        : Freight(id, loc, t, /*cap=*/6)
    {
    }
    size_t maxCapacity() const override { return 6; }
};

#endif // CARGOCRUISER_H
