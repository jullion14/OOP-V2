#ifndef FREIGHTSTORAGE_H
#define FREIGHTSTORAGE_H

#include <vector>
#include <memory>
#include <string>
#include "Freight.h"

class FreightStorage {
    std::vector<std::shared_ptr<Freight>> freights_;
public:
    void loadFreightFromFile(const std::string& filename);
    const std::vector<std::shared_ptr<Freight>>& getFreightList() const {
        return freights_;
    }
};

#endif // FREIGHTSTORAGE_H
