#include "MatchedStorage.h"

#include <fstream>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>    // for std::abs
#include <iostream>

void MatchedStorage::generateMatches(const FreightStorage& fs,
    const CargoStorage& cs)
{
    matchedList_.clear();

    // 1) copy & sort freights by descending capacity
    auto freights = fs.getFreightList();
    std::sort(freights.begin(), freights.end(),
        [](auto const& a, auto const& b) {
            return a->maxCapacity() > b->maxCapacity();
        });

    // 2) track remaining capacity
    std::unordered_map<std::shared_ptr<Freight>, size_t> capRem;
    for (auto const& f : freights)
        capRem[f] = f->maxCapacity();

    // 3) track remaining cargo group sizes
    std::unordered_map<std::shared_ptr<Cargo>, int> cargoRem;
    for (auto const& c : cs.getCargoList())
        cargoRem[c] = c->getGroupSize();

    // 4) match
    for (auto const& c : cs.getCargoList()) {
        time_t ct = c->getTime();
        while (cargoRem[c] > 0) {
            bool loaded = false;
            for (auto const& f : freights) {
                if (f->getLocation() != c->getLocation())          continue;
                if (std::abs(long(f->getTime() - ct)) > 15)         continue;
                if (capRem[f] == 0)                                continue;

                size_t assign = std::min(capRem[f],
                    size_t(cargoRem[c]));
                capRem[f] -= assign;
                cargoRem[c] -= int(assign);

                matchedList_.emplace_back(f, c, assign);
                loaded = true;
                break;
            }
            if (!loaded) break;
        }
    }
}

void MatchedStorage::pruneExpired() {
    matchedList_.erase(
        std::remove_if(matchedList_.begin(),
            matchedList_.end(),
            [](Matcher const& m) { return !m.isValid(); }),
        matchedList_.end());
}

void MatchedStorage::saveSchedule(const std::string& filename,
    const FreightStorage& /*fs*/,
    const CargoStorage& cs) const
{
    std::ofstream out(filename);
    out << "Matched:\n\n";

    // group by freight
    std::map<std::shared_ptr<Freight>, std::vector<Matcher>> groups;
    for (auto const& m : matchedList_) {
        if (!m.isValid()) continue;
        groups[m.getFreight()].push_back(m);
    }

    // print matched
    for (auto const& kv : groups) {
        auto f = kv.first;
        out << "Freight: " << f->getId()
            << " - " << f->getLocation()
            << ", " << f->getTime() << "\n"
            << std::string(50, '-') << "\n";
        for (auto const& m : kv.second) {
            out << m.getCargo()->getId()
                << " - Size: " << m.getAssignedSize() << "\n"
                << std::string(50, '-') << "\n";
        }
        out << "\n";
    }

    // compute unmatched
    std::unordered_map<std::shared_ptr<Cargo>, int> assigned;
    for (auto const& m : matchedList_) {
        if (!m.isValid()) continue;
        assigned[m.getCargo()] += int(m.getAssignedSize());
    }

    out << "Unmatched:\n";
    for (auto const& c : cs.getCargoList()) {
        int rem = c->getGroupSize() - assigned[c];
        if (rem > 0)
            out << c->getId() << " - Size: " << rem << "\n";
    }
}

void MatchedStorage::displaySchedule(const FreightStorage& fs,
    const CargoStorage& cs) const
{
    // exactly the same logic as saveSchedule, but to cout
    std::cout << "Matched:\n\n";

    std::map<std::shared_ptr<Freight>, std::vector<Matcher>> groups;
    for (auto const& m : matchedList_) {
        if (!m.isValid()) continue;
        groups[m.getFreight()].push_back(m);
    }

    for (auto const& kv : groups) {
        auto f = kv.first;
        std::cout << "Freight: " << f->getId()
            << " - " << f->getLocation()
            << ", " << f->getTime() << "\n"
            << std::string(50, '-') << "\n";
        for (auto const& m : kv.second) {
            std::cout << m.getCargo()->getId()
                << " - Size: " << m.getAssignedSize() << "\n"
                << std::string(50, '-') << "\n";
        }
        std::cout << "\n";
    }

    std::unordered_map<std::shared_ptr<Cargo>, int> assigned;
    for (auto const& m : matchedList_) {
        if (!m.isValid()) continue;
        assigned[m.getCargo()] += int(m.getAssignedSize());
    }

    std::cout << "Unmatched:\n";
    for (auto const& c : cs.getCargoList()) {
        int rem = c->getGroupSize() - assigned[c];
        if (rem > 0)
            std::cout << c->getId()
            << " - Size: " << rem << "\n";
    }
}
