// done by: Lim Jia Herng Julian


#pragma once

#include "FreightFactory.h"
#include "MegaCarrier.h"

struct MegaCarrierFactory : FreightFactory {
    std::shared_ptr<Freight>
        create(const std::string& id,
            const std::string& loc,
            time_t t) const override
    {
        std::cout << "[Factory] Creating MegaCarrier(" << id << ")\n";
        return std::make_shared<MegaCarrier>(id, loc, t);
    }
};

