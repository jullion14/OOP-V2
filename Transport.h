#pragma once

#include <string>
#include <ctime>
#include <iostream> 

class Transport {
protected:
    std::string id;
    std::string location;
    time_t time;

public:
    Transport();
    Transport(const std::string& id, const std::string& location, time_t time);

    virtual ~Transport();

    std::string getId() const;
    std::string getLocation() const;
    time_t getTime() const;

    void setId(const std::string& newId);
    void setLocation(const std::string& newLocation);
    void setTime(time_t newTime);

    virtual void printInfo(std::ostream& out = std::cout) const = 0;

};
