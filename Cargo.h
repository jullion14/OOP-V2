#pragma once

#include "Transport.h"
#include <string>
#include <iostream> 

using namespace std;

class Cargo : public Transport {
public:
    Cargo();
    Cargo(const string& id, const string& location, time_t time);

    string getCid() const;
    string getClocation() const;
    time_t getCtime() const;

    void setCid(const string& id);
    void setClocation(const string& location);
    void setCtime(time_t time);

    void printInfo(std::ostream& out = std::cout) const override;

};
