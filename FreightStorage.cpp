#include "FreightStorage.h"
#include "MiniMover.h"
#include "CargoCruiser.h"
#include "MegaCarrier.h"
#include <fstream>
#include <sstream>

void FreightStorage::loadFreightFromFile(const std::string& fn) {
    std::ifstream in(fn);
    if (!in) return;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string id, loc, tstr, type;
        if (!std::getline(ss, id, ','))   continue;
        if (!std::getline(ss, loc, ','))  continue;
        if (!std::getline(ss, tstr, ',')) continue;
        if (!std::getline(ss, type, ',')) continue;

        time_t t = static_cast<time_t>(std::stoll(tstr));
        if (type == "MiniMover") {
            freights_.push_back(
                std::make_shared<MiniMover>(id, loc, t));
        }
        else if (type == "CargoCruiser") {
            freights_.push_back(
                std::make_shared<CargoCruiser>(id, loc, t));
        }
        else if (type == "MegaCarrier") {
            freights_.push_back(
                std::make_shared<MegaCarrier>(id, loc, t));
        }
    }
}
