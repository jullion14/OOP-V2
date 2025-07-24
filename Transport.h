// done by: Chia Jun Xuan

#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <string>
#include <iostream>
#include <ctime>

/**
 * @class Transport
 * @brief Abstract base class for all transport types (e.g., Cargo, Freight).
 *
 * Encapsulates common properties: unique ID, location, and time.
 * Subclasses must implement printInfo for output.
 */
class Transport {
protected:
    std::string id_;        ///< Unique identifier for the transport.
    std::string location_;  ///< Location code or destination.
    time_t      time_;      ///< Time (HHMM integer format).

public:
    /**
     * @brief Construct a Transport with given ID, location, and time.
     * @param id   Unique identifier.
     * @param loc  Location string.
     * @param t    Time (HHMM format).
     */
    Transport(const std::string& id,
        const std::string& loc,
        time_t             t)
        : id_(id), location_(loc), time_(t) {
    }

    virtual ~Transport() = default; ///< Virtual destructor for safe polymorphic use.

    /// @return The transport's unique ID.
    std::string getId() const { return id_; }

    /// @return The current location.
    std::string getLocation() const { return location_; }

    /// @return The time value.
    time_t getTime() const { return time_; }

    /**
     * @brief Update the location string.
     * @param loc New location.
     */
    void setLocation(const std::string& loc) { location_ = loc; }

    /**
     * @brief Update the time value.
     * @param t New time (HHMM).
     */
    void setTime(time_t t) { time_ = t; }

    /**
     * @brief Print details of the transport to the given stream.
     * @param out Output stream.
     */
    virtual void printInfo(std::ostream& out) const = 0;
};

#endif // TRANSPORT_H
