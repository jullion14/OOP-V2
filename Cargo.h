#pragma once

#include "Transport.h"
#include <string>

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
};
