// MiniMover.h
#ifndef MINIMOVER_H
#define MINIMOVER_H

#include "Freight.h"

class MiniMover : public Freight {
public:
    MiniMover(const std::string& id,
        const std::string& loc,
        time_t             t)
        : Freight(id, loc, t, /* capacity */ 50) {
    }

    // these make MiniMover concrete:
    std::string typeName()   const override { return "MiniMover"; }
    size_t      maxCapacity() const override { return 50; }
};

#endif // MINIMOVER_H

