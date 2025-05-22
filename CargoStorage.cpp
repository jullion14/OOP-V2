#include "CargoStorage.h"
#include "FreightStorage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

CargoStorage::CargoStorage() {}

void CargoStorage::loadCargoFromFile(const std::string& filename) {
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
            Cargo cargo(id, location, timeVal);
            addCargo(cargo);
        }
    }
    infile.close();
}

void CargoStorage::addCargo(const Cargo& cargo) {
    cargos.push_back(cargo);
    //std::cout << "Added Cargo: " << cargo.getCid() << std::endl;
}

bool CargoStorage::editCargo(const std::string& id, const std::string& newLocation, time_t newTime) {
    for (auto& c : cargos) {
        if (c.getCid() == id) {
            c.setClocation(newLocation);
            c.setCtime(newTime);
            std::cout << "Edited Cargo: " << id << std::endl;
            return true;
        }
    }
    std::cout << "Cargo not found: " << id << std::endl;
    return false;
}

bool CargoStorage::deleteCargo(const std::string& id) {
    auto it = std::remove_if(cargos.begin(), cargos.end(),
        [&id](const Cargo& c) { return c.getCid() == id; });
    if (it != cargos.end()) {
        cargos.erase(it, cargos.end());
        std::cout << "Deleted Cargo: " << id << std::endl;
        return true;
    }
    std::cout << "Cargo not found: " << id << std::endl;
    return false;
}

void CargoStorage::saveCargoStorage(const std::string& filename) {
    std::cout << "Saving " << cargos.size() << " cargos to " << filename << std::endl;
    // Add file writing logic if needed
}

const std::vector<Cargo>& CargoStorage::getCargoStorage() const {
    return cargos;
}

// Print Cargo and Freight table
void CargoStorage::printCargoTable(const FreightStorage& freightStorage) const {
    const auto& freights = freightStorage.getFreights();
    size_t maxRows = std::max(cargos.size(), freights.size());

    std::cout << std::left << std::setw(10) << "Cargo ID"
        << std::setw(16) << "Destination"
        << std::setw(8) << "Time"
        << "    "
        << std::setw(12) << "Freight ID"
        << std::setw(16) << "Refuel Stop"
        << std::setw(12) << "Refuel Time" << std::endl;
    std::cout << std::string(34, '=') << "    " << std::string(40, '=') << std::endl;

    for (size_t i = 0; i < maxRows; ++i) {
        // Cargo columns
        if (i < cargos.size()) {
            std::cout << std::left << std::setw(10) << cargos[i].getCid()
                << std::setw(16) << cargos[i].getClocation()
                << std::setw(8) << std::setfill('0') << std::setw(4) << cargos[i].getCtime() << std::setfill(' ');
        }
        else {
            std::cout << std::setw(10) << "" << std::setw(16) << "" << std::setw(8) << "";
        }
        std::cout << "    ";
        // Freight columns
        if (i < freights.size()) {
            std::cout << std::left << std::setw(12) << freights[i].getFid()
                << std::setw(16) << freights[i].getFlocation()
                << std::setw(12) << std::setfill('0') << std::setw(4) << freights[i].getFtime() << std::setfill(' ');
        }
        else {
            std::cout << std::setw(12) << "" << std::setw(16) << "" << std::setw(12) << "";
        }
        std::cout << std::endl;
    }
}
