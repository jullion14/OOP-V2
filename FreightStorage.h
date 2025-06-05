#pragma once

#include "Freight.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class FreightStorage {
protected:
    vector<Freight> freights;

public:
    FreightStorage();

    void loadFreightFromFile(const string& filename);
    void addFreight(const Freight& freight);
    bool editFreight(const string& id, const string& newLocation, time_t newTime);
    bool deleteFreight(const string& id);
    void saveFreightStorage(const string& filename);
    const vector<Freight>& getFreights() const;
    string generateNextFreightId() const;
    bool exists(const string& id) const;
    const Freight* getFreightById(const string& id) const;
    const std::vector<Freight>& getFreightList() const;

};
