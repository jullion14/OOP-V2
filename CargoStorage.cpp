#include "CargoStorage.h"
#include <fstream>
#include <sstream>

void CargoStorage::loadCargoFromFile(const std::string& fn) {
    std::ifstream in(fn);
    if (!in) return;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string id, loc, tstr, gstr;
        if (!std::getline(ss, id, ','))   continue;
        if (!std::getline(ss, loc, ','))  continue;
        if (!std::getline(ss, tstr, ',')) continue;
        if (!std::getline(ss, gstr, ',')) continue;

        time_t t = static_cast<time_t>(std::stoll(tstr));
        int    g = std::stoi(gstr);
        cargos_.push_back(std::make_shared<Cargo>(id, loc, t, g));
    }
}
