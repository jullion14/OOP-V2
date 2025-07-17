#ifndef FREIGHT_H
#define FREIGHT_H

#include "Transport.h"
#include "Cargo.h"      // for Cargo&
#include <algorithm>    // for std::min
#include <cassert>      // for assert
#include <cstddef>      // for size_t
#include <iostream>

class Freight : public Transport {
protected:
    size_t remainingCapacity_;
public:
    Freight(const std::string& id,
        const std::string& loc,
        time_t             t,
        size_t             cap)
        : Transport(id, loc, t)
        , remainingCapacity_(cap)
    {
    }

    virtual ~Freight() = default;

    // how much room is left
    size_t getRemainingCapacity() const { return remainingCapacity_; }
    void   setRemainingCapacity(size_t c) { remainingCapacity_ = c; }

    // each subclass returns its own maxCapacity()
    virtual size_t maxCapacity() const = 0;

    // this is the key: pour as much of the cargo batch as will fit,
    // return the cargo's leftover groupSize()
    size_t operator%(Cargo& c) {
        // must be same location
        assert(c.getLocation() == getLocation());
        // how much we can actually load
        size_t assign = std::min(remainingCapacity_,
            static_cast<size_t>(c.getGroupSize()));
        remainingCapacity_ -= assign;
        c.setGroupSize(c.getGroupSize() - assign);
        return static_cast<size_t>(c.getGroupSize());
    }

    void printInfo(std::ostream& out) const override {
        out << "[Freight] ID: " << getId()
            << ", Loc: " << getLocation()
            << ", Time: " << getTime()
            << ", RemCap: " << remainingCapacity_
            << "\n";
    }
};

#endif // FREIGHT_H
