#ifndef MATCHEDSTORAGE_H
#define MATCHEDSTORAGE_H

#include <vector>
#include <string>
#include "Matcher.h"
#include "FreightStorage.h"
#include "CargoStorage.h"

class MatchedStorage {
    std::vector<Matcher> matchedList_;
public:
    void generateMatches(const FreightStorage& fs,
        const CargoStorage& cs);
    void pruneExpired();
    void saveSchedule(const std::string& filename,
        const FreightStorage& fs,
        const CargoStorage& cs) const;
};

#endif // MATCHEDSTORAGE_H
