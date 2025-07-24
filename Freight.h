// Freight.h
#ifndef FREIGHT_H
#define FREIGHT_H

#include <string>
#include <ostream>
#include <ctime>

class Freight {
public:
    Freight(const std::string& id,
        const std::string& loc,
        time_t t,
        size_t cap)
        : id_(id), location_(loc), timestamp_(t), capacity_(cap) {
    }
    virtual ~Freight() = default;

    const std::string& getId()       const { return id_; }
    const std::string& getLocation() const { return location_; }
    time_t              getTime()     const { return timestamp_; }
    size_t              getCap()      const { return capacity_; }

    void setLocation(const std::string& loc) { location_ = loc; }
    void setTime(time_t t) { timestamp_ = t; }

    // new pure?virtual to identify subclass
    virtual std::string typeName() const = 0;
    virtual size_t      maxCapacity() const = 0;

private:
    std::string id_;
    std::string location_;
    time_t      timestamp_;
    size_t      capacity_;
};

// for easy printing, if you like:
inline std::ostream& operator<<(std::ostream& os, const Freight& f) {
    return os
        << f.getId() << ' '
        << f.getLocation() << ' '
        << f.getTime() << ' '
        << f.typeName();
}

#endif // FREIGHT_H
