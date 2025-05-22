#include "CargoStorage.h"
#include <iostream>
#include <fstream>
#include <sstream>
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
