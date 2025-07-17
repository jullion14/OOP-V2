// MatchedStorage.cpp

#include "MatchedStorage.h"
#include <fstream>
#include <map>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cstdlib>    // for std::abs
#include <memory>
#include <string>

void MatchedStorage::generateMatches(const FreightStorage& fs,
    const CargoStorage& cs)
{
    // 1) Copy and sort freights by descending capacity
    std::vector<std::shared_ptr<Freight>> freights = fs.getFreightList();
    std::sort(freights.begin(), freights.end(),
        [](const std::shared_ptr<Freight>& a,
            const std::shared_ptr<Freight>& b) {
                return a->maxCapacity() > b->maxCapacity();
        });

    // 2) For each cargo, pour into the first fitting freight until empty
    for (auto const& cptr : cs.getCargoList()) {
        time_t cargoTime = cptr->getTime();

        while (cptr->getGroupSize() > 0) {
            bool didLoad = false;

            for (auto const& fptr : freights) {
                // location match?
                if (fptr->getLocation() != cptr->getLocation())
                    continue;
                // within ±15 minutes?
                if (std::abs(static_cast<long>(fptr->getTime() - cargoTime)) > 15)
                    continue;
                // has capacity?
                if (fptr->getRemainingCapacity() == 0)
                    continue;

                // pour as much as will fit
                size_t before = cptr->getGroupSize();
                size_t leftover = ((*fptr) % (*cptr));
                size_t assigned = before - leftover;

                // record the partial (or full) load
                matchedList_.emplace_back(fptr, cptr, assigned);

                didLoad = true;
                break;
            }

            if (!didLoad)
                break;  // no more can be loaded for this cargo
        }
    }
}

void MatchedStorage::pruneExpired() {
    matchedList_.erase(
        std::remove_if(matchedList_.begin(), matchedList_.end(),
            [](const Matcher& m) { return !m.isValid(); }),
        matchedList_.end());
}

void MatchedStorage::saveSchedule(const std::string& filename,
    const FreightStorage& fs,
    const CargoStorage& cs) const
{
    std::ofstream out(filename);
    out << "Matched:\n\n";

    // Group all matchers by their freight
    std::map<std::shared_ptr<Freight>, std::vector<Matcher>> groups;
    for (auto const& m : matchedList_) {
        if (!m.isValid()) continue;
        groups[m.getFreight()].push_back(m);
    }

    // Print each freight and its assigned cargos
    for (auto it = groups.begin(); it != groups.end(); ++it) {
        auto fptr = it->first;
        const auto& matches = it->second;

        out << "Freight: " << fptr->getId()
            << " - " << fptr->getLocation()
            << ", " << fptr->getTime()
            << "\n";
        out << std::string(50, '-') << "\n";

        for (auto const& m : matches) {
            out << m.getCargo()->getId()
                << " - Size: " << m.getAssignedSize()
                << "\n";
            out << std::string(50, '-') << "\n";
        }
        out << "\n";
    }

    // Print any cargo with remaining groupSize > 0
    out << "Unmatched:\n";
    for (auto const& cptr : cs.getCargoList()) {
        int leftover = cptr->getGroupSize();
        if (leftover > 0) {
            out << cptr->getId()
                << " - Size: " << leftover
                << "\n";
        }
    }
}
