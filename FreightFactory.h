#pragma once

#include <memory>
#include <string>
#include "Freight.h"

class FreightFactory {
public:
    // the factory method—returns the right subclass
    virtual std::shared_ptr<Freight>
        create(const std::string& id,
            const std::string& loc,
            time_t t) const = 0;

    virtual ~FreightFactory() = default;
};
