#pragma once

#include "Matcher.h"
#include <vector>
#include <string>

class MatchedStorage {
protected:
    std::vector<Matcher> matchedList;

public:
    MatchedStorage();

    void addMatch(const Matcher& match);
    void displayAllMatches() const;
    void saveMatches(const std::string& filename) const;
    const std::vector<Matcher>& getMatchedList() const;
};
