#pragma once

#include "Transport.h"
#include <string>

using namespace std;

class Freight : public Transport {
public:
    Freight();
    Freight(const string& id, const string& location, time_t time);

    string getFid() const;
    string getFlocation() const;
    time_t getFtime() const;

    void setFid(const string& id);
    void setFlocation(const string& location);
    void setFtime(time_t time);
};
