// done by: Loh Kaize Kaiser


#ifndef MATCHER_H
#define MATCHER_H

#include <memory>
#include <iostream>
#include "Freight.h"
#include "Cargo.h"

class Matcher {
    std::weak_ptr<Freight> freight_;
    std::weak_ptr<Cargo>   cargo_;
    size_t                 assignedSize_;  // how many units of this cargo were loaded
public:
    // New ctor that takes assignedSize
    Matcher(const std::shared_ptr<Freight>& f,
        const std::shared_ptr<Cargo>& c,
        size_t                          n)
        : freight_(f), cargo_(c), assignedSize_(n)
    {
    }

    bool isValid() const {
        return !freight_.expired() && !cargo_.expired();
    }

    void displayMatch(std::ostream& out = std::cout) const {
        if (auto f = freight_.lock())
            out << "[Freight] ID: " << f->getId()
            << ", Loc: " << f->getLocation()
            << ", Time: " << f->getTime()
            << "\n";

        if (auto c = cargo_.lock())
            out << "[Cargo]   ID: " << c->getId()
            << ", Assigned: " << assignedSize_
            << "\n";

        out << "\n";
    }

    // Expose for reporting
    std::shared_ptr<Freight> getFreight() const { return freight_.lock(); }
    std::shared_ptr<Cargo>   getCargo()   const { return cargo_.lock(); }
    size_t                   getAssignedSize() const { return assignedSize_; }
};

#endif // MATCHER_H
