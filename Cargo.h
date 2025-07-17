#ifndef CARGO_H
#define CARGO_H

#include "Transport.h"
#include <iostream>

class Cargo : public Transport {
    int groupSize_;
public:
    Cargo(const std::string& id,
        const std::string& loc,
        time_t             t,
        int                g)
        : Transport(id, loc, t)
        , groupSize_(g)
    {
    }

    // how many units this cargo batch needs
    int getGroupSize() const { return groupSize_; }
    // used by operator% to reduce the batch
    void setGroupSize(int g) { groupSize_ = g; }

    void printInfo(std::ostream& out) const override {
        out << "[Cargo]   ID: " << getId()
            << ", Loc: " << getLocation()
            << ", Time: " << getTime()
            << ", Group: " << groupSize_
            << "\n";
    }
};

#endif // CARGO_H
