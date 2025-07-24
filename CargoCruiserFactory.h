// CargoCruiserFactory.h
#pragma once

#include "FreightFactory.h"
#include "CargoCruiser.h"

struct CargoCruiserFactory : FreightFactory {
    std::shared_ptr<Freight>
        create(const std::string& id,
            const std::string& loc,
            time_t t) const override
    {
        std::cout << "[Factory] Creating CargoCruiser(" << id << ")\n";
        return std::make_shared<CargoCruiser>(id, loc, t);
    }
};
