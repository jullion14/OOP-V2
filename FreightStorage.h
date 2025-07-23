#ifndef FREIGHTSTORAGE_H
#define FREIGHTSTORAGE_H

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Freight.h"

class FreightStorage {
    std::vector<std::shared_ptr<Freight>> freights_;
public:
    // Load from file
    void loadFreightFromFile(const std::string& filename);

    // In-memory insert
    void addFreight(const std::shared_ptr<Freight>& freight) {
        freights_.push_back(freight);
    }

    // Remove freight by ID
    bool removeFreightById(const std::string& id) {
        size_t before = freights_.size();
        freights_.erase(
            std::remove_if(freights_.begin(), freights_.end(),
                [&](const std::shared_ptr<Freight>& f) {
                    return f->getId() == id;
                }),
            freights_.end()
        );
        return freights_.size() != before;
    }

    // Accessor
    const std::vector<std::shared_ptr<Freight>>& getFreightList() const {
        return freights_;
    }
};

#endif // FREIGHTSTORAGE_H
