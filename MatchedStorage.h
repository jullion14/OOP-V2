#pragma once

#include "Matcher.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class FreightStorage;
class CargoStorage;

class MatchedStorage {
protected:
    std::vector<Matcher> matchedList;

public:
    MatchedStorage();

    void addMatch(const Matcher& match);
    void displayAllMatches() const;
    void saveMatches(const std::string& filename) const;
    const std::vector<Matcher>& getMatchedList() const;

    void displayScheduleFile(const std::string& filename) const;
    void generateMatches(const FreightStorage& freightStorage, const CargoStorage& cargoStorage,
        std::vector<std::string>& unmatchedFreights, std::vector<std::string>& unmatchedCargos);
};
