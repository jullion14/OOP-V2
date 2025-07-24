// done by: Lim Ding Huang Jonas


#ifndef CARGOSTORAGE_H
#define CARGOSTORAGE_H

#include <vector>
#include <memory>
#include <string>
#include <ostream>
#include "Cargo.h"

class CargoStorage {
    std::vector<std::shared_ptr<Cargo>> cargos_;
public:
    void loadCargoFromFile(const std::string& filename);
    void saveCargoToFile(const std::string& filename) const;

    // in-memory accessor
    const std::vector<std::shared_ptr<Cargo>>& getCargoList() const {
        return cargos_;
    }

    // ID gen
    std::string generateNextCargoId() const;

    // CRUD in memory:
    void addCargo(const std::shared_ptr<Cargo>& cargo);
    bool editCargo(const std::string& id,
        const std::string& newLoc,
        time_t             newTime,
        int                newGroup);
    bool removeCargoById(const std::string& id);

    // display helper
    void displayCargo(std::ostream& out = std::cout) const;
};

#endif // CARGOSTORAGE_H
