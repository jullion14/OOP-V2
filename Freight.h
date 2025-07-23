// Freight.h
#ifndef FREIGHT_H
#define FREIGHT_H

#include "Transport.h"
#include "Cargo.h"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>

class Freight : public Transport {
protected:
    size_t remainingCapacity_;
public:
    Freight(const std::string& id, const std::string& loc, time_t t, size_t cap)
        : Transport(id, loc, t), remainingCapacity_(cap) {
    }
    virtual ~Freight() = default;

    void printInfo(std::ostream& out) const override {
        out << "[Freight] ID: " << id_
            << ", Loc: " << location_
            << ", Time: " << time_
            << ", RemCap: " << remainingCapacity_ << '\n';
    }

    virtual size_t maxCapacity() const = 0;

    size_t getRemainingCapacity() const { return remainingCapacity_; }
    void   setRemainingCapacity(size_t n) { remainingCapacity_ = n; }

    size_t operator%(Cargo& c) {
        assert(c.getLocation() == location_);
        size_t assign = std::min(remainingCapacity_, static_cast<size_t>(c.getGroupSize()));
        remainingCapacity_ -= assign;
        c.setGroupSize(c.getGroupSize() - assign);
        return static_cast<size_t>(c.getGroupSize());
    }
};

#endif // FREIGHT_H