#ifndef CARGOSTORAGE_H
#define CARGOSTORAGE_H

#include <vector>
#include <memory>
#include <string>
#include "Cargo.h"

class CargoStorage {
    std::vector<std::shared_ptr<Cargo>> cargos_;
public:
    void loadCargoFromFile(const std::string& filename);
    const std::vector<std::shared_ptr<Cargo>>& getCargoList() const {
        return cargos_;
    }
};

#endif // CARGOSTORAGE_H
