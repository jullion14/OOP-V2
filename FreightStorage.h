// done by: Lim Ding Huang Jonas

// FreightStorage.h
#ifndef FREIGHTSTORAGE_H
#define FREIGHTSTORAGE_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <iostream>    // for std::cout default param
#include "FreightFactory.h"

/**
 * @class FreightStorage
 * @brief Manages Freight objects with factory-based creation, persistence, and CRUD.
 *
 * Responsibilities:
 *   - Register and use FreightFactory instances for different freight types.
 *   - Load/save freight data from/to files.
 *   - Generate unique freight IDs.
 *   - In-memory management (add, edit, remove) and display of all freights.
 */
class FreightStorage {
    std::vector<std::shared_ptr<Freight>> freights_; ///< In-memory freight list.
    std::map<std::string, std::unique_ptr<FreightFactory>> factories_; ///< Factories by type string.

public:
    /**
     * @brief Register a factory for a given freight type.
     * @param type    String key identifying freight type.
     * @param factory Unique pointer to a FreightFactory.
     */
    void registerFactory(const std::string& type,
        std::unique_ptr<FreightFactory> factory);

    /**
     * @brief Load freight entries from a CSV file.
     * @param filename File path to load from.
     */
    void loadFreightFromFile(const std::string& filename);

    /**
     * @brief Save all freight entries to a CSV file.
     * @param filename File path to save to.
     */
    void saveFreightToFile(const std::string& filename) const;

    /**
     * @brief Get read-only access to the list of Freight objects.
     * @return Const reference to vector of shared pointers.
     */
    const std::vector<std::shared_ptr<Freight>>& getFreightList() const {
        return freights_;
    }

    /**
     * @brief Get the factory for a type key (or nullptr if missing).
     * @param key String key for the factory.
     * @return Pointer to registered FreightFactory, or nullptr.
     */
    FreightFactory* getFactory(const std::string& key) const {
        auto it = factories_.find(key);
        return it == factories_.end()
            ? nullptr
            : it->second.get();
    }

    /**
     * @brief Generate the next available unique freight ID (e.g., F01, F02).
     * @return Next freight ID as string.
     */
    std::string generateNextFreightId() const;

    /**
     * @brief Add a new Freight to storage.
     * @param freight Shared pointer to the Freight to add.
     */
    void addFreight(const std::shared_ptr<Freight>& freight);

    /**
     * @brief Edit an existing freight entry (by ID).
     * @param id       Freight ID to edit.
     * @param newLoc   New location code.
     * @param newTime  New available time.
     * @param newType  Numeric code for new type (0 = keep current).
     * @return true if edit succeeded, false otherwise.
     */
    bool editFreight(const std::string& id,
        const std::string& newLoc,
        time_t             newTime,
        int                newType);

    /**
     * @brief Remove a freight entry by ID.
     * @param id Freight ID to remove.
     * @return true if removal succeeded, false otherwise.
     */
    bool removeFreightById(const std::string& id);

    /**
     * @brief Display all freights in a table format.
     * @param out Output stream (default: std::cout).
     */
    void displayFreight(std::ostream& out = std::cout) const;
};

#endif // FREIGHTSTORAGE_H
