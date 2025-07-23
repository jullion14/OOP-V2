#include "CargoStorage.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

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

void CargoStorage::saveCargoToFile(const std::string& fn) const {
    std::ofstream out(fn);
    for (auto const& c : cargos_) {
        out << c->getId() << ','
            << c->getLocation() << ','
            << c->getTime() << ','
            << c->getGroupSize() << "\n";
    }
}

std::string CargoStorage::generateNextCargoId() const {
    int maxNum = 0;
    for (auto const& c : cargos_) {
        auto id = c->getId();
        if (id.size() > 1 && id[0] == 'C') {
            maxNum = std::max(maxNum, std::stoi(id.substr(1)));
        }
    }
    std::ostringstream oss;
    oss << 'C' << std::setw(2) << std::setfill('0') << (maxNum + 1);
    return oss.str();
}

void CargoStorage::addCargo(const std::shared_ptr<Cargo>& cargo) {
    cargos_.push_back(cargo);
}

bool CargoStorage::editCargo(const std::string& id,
    const std::string& newLoc,
    time_t             newTime,
    int                newGroup)
{
    for (auto& c : cargos_) {
        if (c->getId() == id) {
            c->setLocation(newLoc);
            c->setTime(newTime);
            c->setGroupSize(newGroup);
            return true;
        }
    }
    return false;
}

bool CargoStorage::removeCargoById(const std::string& id) {
    auto before = cargos_.size();
    cargos_.erase(
        std::remove_if(cargos_.begin(), cargos_.end(),
            [&](auto const& c) { return c->getId() == id; }),
        cargos_.end());
    return cargos_.size() != before;
}

void CargoStorage::displayCargo(std::ostream& out) const {
    out << std::left
        << std::setw(10) << "C_ID"
        << std::setw(15) << "Destination"
        << std::setw(8) << "Time"
        << std::setw(8) << "Group"
        << "\n" << std::string(10 + 15 + 8 + 8, '-') << "\n";
    for (auto const& c : cargos_) {
        out << std::setw(10) << c->getId()
            << std::setw(15) << c->getLocation()
            << std::setw(8) << c->getTime()
            << std::setw(8) << c->getGroupSize()
            << "\n";
    }
}
