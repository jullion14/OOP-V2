// done by: Loh Kaize Kaiser


#ifndef MATCHEDSTORAGE_H
#define MATCHEDSTORAGE_H

#include <vector>
#include <string>
#include <memory>                // added
#include "Matcher.h"
#include "FreightStorage.h"
#include "CargoStorage.h"
#include "MatchStrategy.h"       // added

class MatchedStorage {
    std::vector<Matcher> matchedList_;

    // NEW: strategy pointer
    std::unique_ptr<MatchStrategy> strategy_;

public:
    // allow caller to pick which matching rule to use
    void setStrategy(std::unique_ptr<MatchStrategy> s) {
        strategy_ = std::move(s);
    }

    void generateMatches(const FreightStorage& fs,
        const CargoStorage& cs);
    void pruneExpired();
    void saveSchedule(const std::string& filename,
        const FreightStorage& fs,
        const CargoStorage& cs) const;

    // display matched + unmatched to console
    void displaySchedule(const FreightStorage& fs,
        const CargoStorage& cs) const;
};

#endif // MATCHEDSTORAGE_H

