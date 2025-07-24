// done by: Chia Jun Xuan

// Freight.h
#ifndef FREIGHT_H
#define FREIGHT_H

#include <string>
#include <ostream>
#include <ctime>

/**
 * @class Freight
 * @brief Abstract base class for all transport vehicles that can carry cargo.
 *
 * Holds common attributes: unique ID, location, available time, and capacity.
 * Defines interface for type and maximum capacity (for different freight subtypes).
 */
class Freight {
public:
    /**
     * @brief Construct a Freight instance.
     * @param id   Unique identifier for the freight.
     * @param loc  Location code.
     * @param t    Time in HHMM format.
     * @param cap  Configured (default) capacity.
     */
    Freight(const std::string& id,
        const std::string& loc,
        time_t             t,
        size_t             cap)
        : id_(id), location_(loc), timestamp_(t), capacity_(cap) {
    }

    virtual ~Freight() = default;

    /// @return The freight's unique ID.
    const std::string& getId() const { return id_; }

    /// @return The location (as string).
    const std::string& getLocation() const { return location_; }

    /// @return The time value (HHMM as integer).
    time_t getTime() const { return timestamp_; }

    /// @return The (default) capacity value.
    size_t getCap() const { return capacity_; }

    /// Set a new location.
    void setLocation(const std::string& loc) { location_ = loc; }

    /// Set a new time value.
    void setTime(time_t t) { timestamp_ = t; }

    /**
     * @brief Return the type name of the derived freight.
     * @return Subclass-specific type name string.
     */
    virtual std::string typeName() const = 0;

    /**
     * @brief Return the maximum loadable capacity.
     * @return Subclass-specific max capacity.
     */
    virtual size_t maxCapacity() const = 0;

private:
    std::string id_;
    std::string location_;
    time_t      timestamp_;
    size_t      capacity_;
};

/**
 * @brief Print short info for a Freight (ID, location, time, type).
 * @param os Output stream.
 * @param f  Reference to Freight.
 * @return Reference to stream for chaining.
 */
inline std::ostream& operator<<(std::ostream& os, const Freight& f) {
    return os
        << f.getId() << ' '
        << f.getLocation() << ' '
        << f.getTime() << ' '
        << f.typeName();
}

#endif // FREIGHT_H
