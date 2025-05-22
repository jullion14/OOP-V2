#pragma once

#include "Matcher.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class FreightStorage;
class CargoStorage;

class MatchedStorage {
protected:
    vector<Matcher> matchedList;

public:
    MatchedStorage();

    void addMatch(const Matcher& match);
    void displayAllMatches(const vector<string>& unmatchedFreights, const vector<string>& unmatchedCargos) const;
    void saveMatches(const string& filename,
        const vector<string>& unmatchedFreights,
        const vector<string>& unmatchedCargos) const;
    const vector<Matcher>& getMatchedList() const;

    void displayScheduleFile(const string& filename) const;
    void generateMatches(const FreightStorage& freightStorage,
        const CargoStorage& cargoStorage,
        vector<string>& unmatchedFreights,
        vector<string>& unmatchedCargos);
};
