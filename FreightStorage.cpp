#include "FreightStorage.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

FreightStorage::FreightStorage() {}

void FreightStorage::loadFreightFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cout << "Cannot open file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string id, location, timeStr;
        if (std::getline(ss, id, ',') && std::getline(ss, location, ',') && std::getline(ss, timeStr)) {
            time_t timeVal = std::stoi(timeStr);
            Freight freight(id, location, timeVal);
            addFreight(freight);
        }
    }
    infile.close();
}

void FreightStorage::addFreight(const Freight& freight) {
    freights.push_back(freight);
    // std::cout << "Added Freight: " << freight.getFid() << std::endl;
}

bool FreightStorage::editFreight(const std::string& id, const std::string& newLocation, time_t newTime) {
    for (auto& f : freights) {
        if (f.getFid() == id) {
            f.setFlocation(newLocation);
            f.setFtime(newTime);
            std::cout << "Edited Freight: " << id << std::endl;
            return true;
        }
    }
    std::cout << "Freight not found: " << id << std::endl;
    return false;
}

bool FreightStorage::deleteFreight(const std::string& id) {
    auto it = std::remove_if(freights.begin(), freights.end(),
        [&id](const Freight& f) { return f.getFid() == id; });
    if (it != freights.end()) {
        freights.erase(it, freights.end());
        std::cout << "Deleted Freight: " << id << std::endl;
        return true;
    }
    std::cout << "Freight not found: " << id << std::endl;
    return false;
}

void FreightStorage::saveFreightStorage(const std::string& filename) {
    std::cout << "Saving " << freights.size() << " freights to " << filename << std::endl;
    // Add file writing logic if needed
}

const std::vector<Freight>& FreightStorage::getFreights() const {
    return freights;
}
