#include "MatchedStorage.h"
#include "FreightStorage.h"
#include "CargoStorage.h"
#include <fstream>
#include <iostream>
#include <algorithm>

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

void MatchedStorage::displayScheduleFile(const std::string& filename) const {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cout << "Error: Could not open file '" << filename << "' for reading." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
    }
    inputFile.close();
}

void MatchedStorage::generateMatches(const FreightStorage& freightStorage, const CargoStorage& cargoStorage,
    std::vector<std::string>& unmatchedFreights, std::vector<std::string>& unmatchedCargos) {
    matchedList.clear();
    unmatchedFreights.clear();
    unmatchedCargos.clear();

    const auto& freights = freightStorage.getFreights();
    const auto& cargos = cargoStorage.getCargoStorage();
    std::vector<bool> cargoMatched(cargos.size(), false);

    for (const auto& freight : freights) {
        bool foundMatch = false;
        for (size_t i = 0; i < cargos.size(); ++i) {
            if (!cargoMatched[i] &&
                freight.getFlocation() == cargos[i].getClocation() &&
                freight.getFtime() == cargos[i].getCtime()) {
                Matcher match(freight, cargos[i]);
                addMatch(match);
                cargoMatched[i] = true;
                foundMatch = true;
                break;
            }
        }
        if (!foundMatch) {
            unmatchedFreights.push_back(freight.getFid());
        }
    }
    for (size_t i = 0; i < cargos.size(); ++i) {
        if (!cargoMatched[i]) {
            unmatchedCargos.push_back(cargos[i].getCid());
        }
    }
}
