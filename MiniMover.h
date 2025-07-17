#ifndef MINIMOVER_H
#define MINIMOVER_H

#include "Freight.h"

class MiniMover : public Freight {
public:
    MiniMover(const std::string& id,
        const std::string& loc,
        time_t             t)
        : Freight(id, loc, t, /*cap=*/2)
    {
    }
    size_t maxCapacity() const override { return 2; }
};

#endif // MINIMOVER_H
