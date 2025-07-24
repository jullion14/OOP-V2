// done by: Chia Jun Xuan

// Cargo.h
#ifndef CARGO_H
#define CARGO_H

#include "Transport.h"
#include <iostream>

/**
 * @class Cargo
 * @brief Represents a group of items to be transported, inheriting base transport info.
 *
 * Adds a group size attribute on top of the basic Transport (id, location, time).
 */
class Cargo : public Transport {
protected:
    int groupSize_; ///< Number of items in this cargo batch.
public:
    /**
     * @brief Construct a Cargo with given ID, location, time, and group size.
     * @param id  Unique identifier for this cargo.
     * @param loc Destination or stop code.
     * @param t   Time (HHMM integer format).
     * @param g   Number of items in the group.
     */
    Cargo(const std::string& id, const std::string& loc, time_t t, int g)
        : Transport(id, loc, t), groupSize_(g) {
    }

    /**
     * @brief Print details of this cargo to the given stream.
     * @param out Output stream.
     */
    void printInfo(std::ostream& out) const override {
        out << "[Cargo]   ID: " << id_
            << ", Loc: " << location_
            << ", Time: " << time_
            << ", Group: " << groupSize_ << '\n';
    }

    /// @return The group size (number of people/items in this cargo).
    int getGroupSize() const { return groupSize_; }

    /**
     * @brief Set the group size to a new value.
     * @param n New group size.
     */
    void setGroupSize(int n) { groupSize_ = n; }
};

#endif // CARGO_H
