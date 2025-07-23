// Transport.h
#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <string>
#include <iostream>
#include <ctime>

class Transport {
protected:
    std::string id_;
    std::string location_;
    time_t      time_;
public:
    Transport(const std::string& id, const std::string& loc, time_t t)
        : id_(id), location_(loc), time_(t) {
    }
    virtual ~Transport() = default;

    std::string getId() const { return id_; }
    std::string getLocation() const { return location_; }
    time_t      getTime() const { return time_; }

    void setLocation(const std::string& loc) { location_ = loc; }
    void setTime(time_t t) { time_ = t; }

    virtual void printInfo(std::ostream& out) const = 0;
};

#endif // TRANSPORT_H