// MatchedStorage.cpp

#include "MatchedStorage.h"

#include <fstream>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>    // for std::abs
#include <iostream>
#include <iomanip>    // for setw, setfill
#include <sstream>    // for ostringstream

#include "TimeWindowStrategy.h"

void MatchedStorage::generateMatches(const FreightStorage& fs,
    const CargoStorage& cs)
{
    // default to +/-15 min if no strategy set
    if (!strategy_) {
        strategy_ = std::make_unique<TimeWindowStrategy>(15);
    }

    matchedList_.clear();

    // 1) sort freights by descending capacity
    auto freights = fs.getFreightList();
    std::sort(freights.begin(), freights.end(),
        [](auto const& a, auto const& b) {
            return a->maxCapacity() > b->maxCapacity();
        });

    // 2) track remaining capacity
    std::unordered_map<std::shared_ptr<Freight>, size_t> capRem;
    for (auto const& f : freights) {
        capRem[f] = f->maxCapacity();
    }

    // 3) track remaining cargo
    std::unordered_map<std::shared_ptr<Cargo>, int> cargoRem;
    for (auto const& c : cs.getCargoList()) {
        cargoRem[c] = c->getGroupSize();
    }

    // 4) matching loop
    for (auto const& c : cs.getCargoList()) {
        while (cargoRem[c] > 0) {
            bool loaded = false;
            for (auto const& f : freights) {
                if (!strategy_->canMatch(*f, *c)) {
                    continue;
                }
                if (capRem[f] == 0) {
                    continue;
                }

                size_t assign = std::min(capRem[f],
                    static_cast<size_t>(cargoRem[c]));
                capRem[f] -= assign;
                cargoRem[c] -= static_cast<int>(assign);

                matchedList_.emplace_back(f, c, assign);
                loaded = true;
                break;
            }
            if (!loaded) {
                break;
            }
        }
    }
}

void MatchedStorage::pruneExpired()
{
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

        // zero-pad freight time
        std::ostringstream tf;
        tf << std::setw(4) << std::setfill('0') << f->getTime();

        out << "Freight: " << f->getId()
            << " - " << f->getLocation()
            << ", " << tf.str() << "\n"
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
        // <— explicit cast removes the warning here
        assigned[m.getCargo()] += static_cast<int>(m.getAssignedSize());
    }

    out << "Unmatched:\n";
    for (auto const& c : cs.getCargoList()) {
        int rem = c->getGroupSize() - assigned[c];
        if (rem > 0) {
            out << c->getId() << " - Size: " << rem << "\n";
        }
    }
}

void MatchedStorage::displaySchedule(const FreightStorage& fs,
    const CargoStorage& cs) const
{
    std::cout << "Matched:\n\n";

    // group by freight
    std::map<std::shared_ptr<Freight>, std::vector<Matcher>> groups;
    for (auto const& m : matchedList_) {
        if (!m.isValid()) continue;
        groups[m.getFreight()].push_back(m);
    }

    // print matched
    for (auto const& kv : groups) {
        auto f = kv.first;

        std::ostringstream tf;
        tf << std::setw(4) << std::setfill('0') << f->getTime();

        std::cout << "Freight: " << f->getId()
            << " - " << f->getLocation()
            << ", " << tf.str() << "\n"
            << std::string(50, '-') << "\n";

        for (auto const& m : kv.second) {
            std::cout << m.getCargo()->getId()
                << " - Size: " << m.getAssignedSize() << "\n"
                << std::string(50, '-') << "\n";
        }
        std::cout << "\n";
    }

    // compute unmatched
    std::unordered_map<std::shared_ptr<Cargo>, int> assigned;
    for (auto const& m : matchedList_) {
        if (!m.isValid()) continue;
        // <— and here as well
        assigned[m.getCargo()] += static_cast<int>(m.getAssignedSize());
    }

    std::cout << "Unmatched:\n";
    for (auto const& c : cs.getCargoList()) {
        int rem = c->getGroupSize() - assigned[c];
        if (rem > 0) {
            std::cout << c->getId() << " - Size: " << rem << "\n";
        }
    }
}
