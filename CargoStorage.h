// done by: Lim Ding Huang Jonas

#ifndef CARGOSTORAGE_H
#define CARGOSTORAGE_H

#include <vector>
#include <memory>
#include <string>
#include <ostream>
#include "Cargo.h"

/**
 * @class CargoStorage
 * @brief Manages a list of Cargo objects with file I/O and CRUD operations.
 *
 * Provides loading/saving to CSV files, unique ID generation, and
 * in-memory management (add, edit, remove, display) of all cargo entries.
 */
class CargoStorage {
    std::vector<std::shared_ptr<Cargo>> cargos_; ///< All cargo records in memory.
public:
    /**
     * @brief Load cargo entries from a CSV file.
     * @param filename Path to the file to load from.
     */
    void loadCargoFromFile(const std::string& filename);

    /**
     * @brief Save all cargo entries to a CSV file.
     * @param filename Path to the file to save to.
     */
    void saveCargoToFile(const std::string& filename) const;

    /**
     * @brief Get read-only access to the current cargo list.
     * @return Const reference to vector of Cargo shared pointers.
     */
    const std::vector<std::shared_ptr<Cargo>>& getCargoList() const {
        return cargos_;
    }

    /**
     * @brief Generate the next available cargo ID (e.g., C01, C02).
     * @return Unique cargo ID as string.
     */
    std::string generateNextCargoId() const;

    /**
     * @brief Add a new Cargo object to storage.
     * @param cargo Shared pointer to the Cargo to add.
     */
    void addCargo(const std::shared_ptr<Cargo>& cargo);

    /**
     * @brief Edit an existing cargo entry (by ID).
     * @param id       ID of cargo to edit.
     * @param newLoc   New location.
     * @param newTime  New time value.
     * @param newGroup New group size.
     * @return true if edit succeeded, false if ID not found.
     */
    bool editCargo(const std::string& id,
        const std::string& newLoc,
        time_t             newTime,
        int                newGroup);

    /**
     * @brief Remove a cargo entry by ID.
     * @param id Cargo ID to remove.
     * @return true if removal succeeded, false if ID not found.
     */
    bool removeCargoById(const std::string& id);

    /**
     * @brief Display all cargo entries in table format.
     * @param out Output stream (defaults to std::cout).
     */
    void displayCargo(std::ostream& out = std::cout) const;
};

#endif // CARGOSTORAGE_H
