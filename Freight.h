#ifndef FREIGHT_H
#define FREIGHT_H

#include "Transport.h"
#include "Cargo.h"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
using namespace std;

class Freight : public Transport {
protected:
    size_t remainingCapacity_;
public:
    Freight(const string& id,
        const string& loc,
        time_t         t,
        size_t         cap)
        : Transport(id, loc, t)
        , remainingCapacity_(cap)
    {
    }

    virtual ~Freight() = default;

    size_t getRemainingCapacity() const { return remainingCapacity_; }
    void   setRemainingCapacity(size_t c) { remainingCapacity_ = c; }

    virtual size_t maxCapacity() const = 0;

    size_t operator%(Cargo& c) {
        assert(c.getLocation() == getLocation());
        size_t assign = min(remainingCapacity_,
            static_cast<size_t>(c.getGroupSize()));
        remainingCapacity_ -= assign;
        int leftover = c.getGroupSize() - static_cast<int>(assign);
        c.setGroupSize(leftover);
        return static_cast<size_t>(leftover);
    }

    void printInfo(ostream& out) const override {
        out << "[Freight] ID: " << getId()
            << ", Loc: " << getLocation()
            << ", Time: " << getTime()
            << ", RemCap: " << remainingCapacity_
            << "\n";
    }
};

#endif // FREIGHT_H
