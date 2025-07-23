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
        return std::make_shared<CargoCruiser>(id, loc, t);
    }
};
