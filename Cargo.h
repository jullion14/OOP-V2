// done by: Chia Jun Xuan


// Cargo.h
#ifndef CARGO_H
#define CARGO_H

#include "Transport.h"
#include <iostream>

class Cargo : public Transport {
protected:
    int groupSize_;
public:
    Cargo(const std::string& id, const std::string& loc, time_t t, int g)
        : Transport(id, loc, t), groupSize_(g) {
    }

    void printInfo(std::ostream& out) const override {
        out << "[Cargo]   ID: " << id_
            << ", Loc: " << location_
            << ", Time: " << time_
            << ", Group: " << groupSize_ << '\n';
    }

    int getGroupSize() const { return groupSize_; }
    void setGroupSize(int n) { groupSize_ = n; }
};

#endif // CARGO_H