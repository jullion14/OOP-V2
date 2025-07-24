// FreightFactory.h
#ifndef FREIGHTFACTORY_H
#define FREIGHTFACTORY_H

#include <memory>
#include "Freight.h"

// Abstract factory interface
struct FreightFactory {
    virtual ~FreightFactory() = default;
    virtual std::shared_ptr<Freight>
        create(const std::string& id,
            const std::string& loc,
            time_t             t) const = 0;
};

#endif // FREIGHTFACTORY_H
