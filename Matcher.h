// done by: Loh Kaize Kaiser

#ifndef MATCHER_H
#define MATCHER_H

#include <memory>
#include <iostream>
#include "Freight.h"
#include "Cargo.h"

/**
 * @class Matcher
 * @brief Represents a pairing between a Freight and a Cargo, with quantity assigned.
 *
 * Holds weak pointers to avoid memory leaks, and the number of cargo units loaded.
 */
class Matcher {
    std::weak_ptr<Freight> freight_;   ///< Matched freight vehicle (weak pointer).
    std::weak_ptr<Cargo>   cargo_;     ///< Matched cargo group (weak pointer).
    size_t                 assignedSize_; ///< How many units of this cargo were assigned.

public:
    /**
     * @brief Construct a Matcher with specific assignments.
     * @param f Shared pointer to Freight.
     * @param c Shared pointer to Cargo.
     * @param n Number of units assigned in this match.
     */
    Matcher(const std::shared_ptr<Freight>& f,
        const std::shared_ptr<Cargo>& c,
        size_t                        n)
        : freight_(f), cargo_(c), assignedSize_(n)
    {
    }

    /**
     * @brief Check if both pointers (freight and cargo) are still valid.
     * @return True if both are alive.
     */
    bool isValid() const {
        return !freight_.expired() && !cargo_.expired();
    }

    /**
     * @brief Print the match details to an output stream.
     * @param out Output stream, defaults to std::cout.
     */
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

    /// @return Shared pointer to matched Freight, or nullptr if expired.
    std::shared_ptr<Freight> getFreight() const { return freight_.lock(); }
    /// @return Shared pointer to matched Cargo, or nullptr if expired.
    std::shared_ptr<Cargo>   getCargo()   const { return cargo_.lock(); }
    /// @return Number of cargo units assigned in this match.
    size_t                   getAssignedSize() const { return assignedSize_; }
};

#endif // MATCHER_H
