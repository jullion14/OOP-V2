#pragma once
#include "Cargo.h"
#include <vector>
#include <string>

class CargoStorage {
protected:
    std::vector<Cargo> cargos;

public:
    CargoStorage();

    void loadCargoFromFile(const std::string& filename);
    void addCargo(const Cargo& cargo);
    bool editCargo(const std::string& id, const std::string& newLocation, time_t newTime);
    bool deleteCargo(const std::string& id);
    void saveCargoStorage(const std::string& filename);
    const std::vector<Cargo>& getCargoStorage() const;
};
