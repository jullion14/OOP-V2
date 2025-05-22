#pragma once

#include "Freight.h"
#include <vector>
#include <string>
#include <iostream>

class FreightStorage {
protected:
    std::vector<Freight> freights;

public:
    FreightStorage();

    void loadFreightFromFile(const std::string& filename);
    void addFreight(const Freight& freight);
    bool editFreight(const std::string& id, const std::string& newLocation, time_t newTime);
    bool deleteFreight(const std::string& id);
    void saveFreightStorage(const std::string& filename);
    const std::vector<Freight>& getFreights() const;
};
