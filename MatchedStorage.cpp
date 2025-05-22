#include "MatchedStorage.h"
#include <iostream>
#include <fstream>

MatchedStorage::MatchedStorage() {}

void MatchedStorage::addMatch(const Matcher& match) {
    matchedList.push_back(match);
}

void MatchedStorage::displayAllMatches() const {
    if (matchedList.empty()) {
        std::cout << "No matched freight-cargo pairs.\n";
        return;
    }
    std::cout << "Matched Freight-Cargo Pairs:\n";
    for (const auto& match : matchedList) {
        match.displayMatch();
    }
}

void MatchedStorage::saveMatches(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cout << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    for (const auto& match : matchedList) {
        ofs << "Freight: " << match.getFreight().getFid()
            << " (" << match.getFreight().getFlocation() << ", " << match.getFreight().getFtime() << ")"
            << " <--> "
            << "Cargo: " << match.getCargo().getCid()
            << " (" << match.getCargo().getClocation() << ", " << match.getCargo().getCtime() << ")"
            << std::endl;
    }
    ofs.close();
    std::cout << "Matches saved to " << filename << std::endl;
}

const std::vector<Matcher>& MatchedStorage::getMatchedList() const {
    return matchedList;
}
