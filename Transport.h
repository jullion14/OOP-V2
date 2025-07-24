// done by: Chia Jun Xuan


#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <string>
#include <iostream>
#include <ctime>

using namespace std;

class Transport {
protected:
    string id_;
    string location_;
    time_t      time_;
public:
    Transport(const string& id,
        const string& loc,
        time_t             t)
        : id_(id), location_(loc), time_(t) {
    }

    virtual ~Transport() = default;

    string getId()       const { return id_; }
    string getLocation() const { return location_; }
    time_t      getTime()     const { return time_; }

    // from UML
    void setLocation(const string& loc) { location_ = loc; }
    void setTime(time_t t) { time_ = t; }

    virtual void printInfo(ostream& out) const = 0;
};

#endif // TRANSPORT_H
