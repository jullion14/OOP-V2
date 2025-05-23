#pragma once

#include "Cargo.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class FreightStorage; 

class CargoStorage {
protected:
    vector<Cargo> cargos;

public:
    CargoStorage();

    void loadCargoFromFile(const string& filename);
    void addCargo(const Cargo& cargo);
    bool editCargo(const string& id, const string& newLocation, time_t newTime);
    bool deleteCargo(const string& id);
    void saveCargoStorage(const string& filename);
    const vector<Cargo>& getCargoStorage() const;
    void printCargoTable(const FreightStorage& freightStorage) const;
    string generateNextCargoId() const;
    bool exists(const string& id) const;
};
