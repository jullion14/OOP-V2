// FreightStorage.h
#ifndef FREIGHTSTORAGE_H
#define FREIGHTSTORAGE_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <iostream>    // for std::cout in default args
#include "FreightFactory.h"

class FreightStorage {
    std::vector<std::shared_ptr<Freight>> freights_;
    std::map<std::string, std::unique_ptr<FreightFactory>> factories_;

public:
    // Register a concrete factory under the given key
    void registerFactory(const std::string& type,
        std::unique_ptr<FreightFactory> factory);

    // Load/save CSV
    void loadFreightFromFile(const std::string& filename);
    void saveFreightToFile(const std::string& filename) const;

    // Accessors
    const std::vector<std::shared_ptr<Freight>>& getFreightList() const {
        return freights_;
    }

    // **NEW**: expose the factory by key
    // returns nullptr if the key isn't registered
    FreightFactory* getFactory(const std::string& key) const {
        auto it = factories_.find(key);
        return it == factories_.end()
            ? nullptr
            : it->second.get();
    }

    // ID + CRUD
    std::string generateNextFreightId() const;
    void addFreight(const std::shared_ptr<Freight>& freight);
    bool editFreight(const std::string& id,
        const std::string& newLoc,
        time_t         newTime,
        int            newType);
    bool removeFreightById(const std::string& id);

    // Display helper
    void displayFreight(std::ostream& out = std::cout) const;
};

#endif // FREIGHTSTORAGE_H
