// done by: Lim Jia Herng Julian


#pragma once

#include "FreightFactory.h"
#include "MiniMover.h"

struct MiniMoverFactory : FreightFactory {
    std::shared_ptr<Freight>
        create(const std::string& id,
            const std::string& loc,
            time_t t) const override
    {
        std::cout << "[Factory] Creating MiniMover(" << id << ")\n";
        return std::make_shared<MiniMover>(id, loc, t);
    }
};
