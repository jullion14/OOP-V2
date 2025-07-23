#ifndef CARGOSTORAGE_H
#define CARGOSTORAGE_H

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Cargo.h"

class CargoStorage {
    std::vector<std::shared_ptr<Cargo>> cargos_;
public:
    // Load from file
    void loadCargoFromFile(const std::string& filename);

    // In-memory insert
    void addCargo(const std::shared_ptr<Cargo>& cargo) {
        cargos_.push_back(cargo);
    }

    // Remove cargo by ID
    bool removeCargoById(const std::string& id) {
        size_t before = cargos_.size();
        cargos_.erase(
            std::remove_if(cargos_.begin(), cargos_.end(),
                [&](const std::shared_ptr<Cargo>& c) {
                    return c->getId() == id;
                }),
            cargos_.end()
        );
        return cargos_.size() != before;
    }

    // Accessor
    const std::vector<std::shared_ptr<Cargo>>& getCargoList() const {
        return cargos_;
    }
};

#endif // CARGOSTORAGE_H
