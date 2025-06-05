#include "MatchedStorage.h"
#include "FreightStorage.h"
#include "CargoStorage.h"
#include "Freight.h"
#include "Cargo.h"
#include "Transport.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

MatchedStorage::MatchedStorage() {}

void MatchedStorage::addMatch(const Matcher& match) {
    matchedList.push_back(match);
}

void MatchedStorage::displayAllMatches(
    const vector<string>& unmatchedFreights,
    const vector<string>& unmatchedCargos,
    const FreightStorage& freightStorage,
    const CargoStorage& cargoStorage) const
{
    cout << "\n===== Matched Freight-Cargo Pairs =====\n";
    if (matchedList.empty()) {
        cout << "No matched freight-cargo pairs.\n";
    }
    else {
        for (const auto& match : matchedList) {
            Transport* t1 = new Freight(match.getFreight());
            Transport* t2 = new Cargo(match.getCargo());

            cout << "[MATCH]\n";
            t1->printInfo();
            t2->printInfo();
            cout << endl;

            delete t1;
            delete t2;
        }
    }

    // ===== Unmatched Freights =====
    cout << "\n===== Unmatched Freights =====\n";
    if (unmatchedFreights.empty()) {
        cout << "None\n";
    }
    else {
        for (const auto& id : unmatchedFreights) {
            const Freight* f = freightStorage.getFreightById(id);
            if (f) {
                Transport* t = new Freight(*f);
                t->printInfo();
                delete t;
            }
        }
    }

    // ===== Unmatched Cargos =====
    cout << "\n===== Unmatched Cargos =====\n";
    if (unmatchedCargos.empty()) {
        cout << "None\n";
    }
    else {
        for (const auto& id : unmatchedCargos) {
            const Cargo* c = cargoStorage.getCargoById(id);
            if (c) {
                Transport* t = new Cargo(*c);
                t->printInfo();
                delete t;
            }
        }
    }
}

void MatchedStorage::saveMatches(const string& filename,
    const vector<string>& unmatchedFreights,
    const vector<string>& unmatchedCargos) const {
    ofstream ofs(filename);
    if (!ofs) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }

    ofs << "===== Matched Freight-Cargo Pairs =====\n";
    if (matchedList.empty()) {
        ofs << "No matched freight-cargo pairs.\n";
    }
    else {
        for (const auto& match : matchedList) {
            Transport* t1 = new Freight(match.getFreight());
            Transport* t2 = new Cargo(match.getCargo());

            ofs << "[MATCH]\n";
            t1->printInfo(ofs);
            t2->printInfo(ofs);
            ofs << "\n";

            delete t1;
            delete t2;
        }
    }

    ofs << "\n===== Unmatched Freights =====\n";
    if (unmatchedFreights.empty()) {
        ofs << "None\n";
    }
    else {
        for (const auto& fid : unmatchedFreights) {
            ofs << "- " << fid << "\n";
        }
    }

    ofs << "\n===== Unmatched Cargos =====\n";
    if (unmatchedCargos.empty()) {
        ofs << "None\n";
    }
    else {
        for (const auto& cid : unmatchedCargos) {
            ofs << "- " << cid << "\n";
        }
    }

    ofs.close();
    cout << "Matches saved to " << filename << endl;
}


const vector<Matcher>& MatchedStorage::getMatchedList() const {
    return matchedList;
}

void MatchedStorage::displayScheduleFile(const string& filename) const {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Error: Could not open file '" << filename << "' for reading." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }

    inputFile.close();
}

void MatchedStorage::generateMatches(const FreightStorage& freightStorage,
    const CargoStorage& cargoStorage,
    vector<string>& unmatchedFreights,
    vector<string>& unmatchedCargos) {
    matchedList.clear();
    unmatchedFreights.clear();
    unmatchedCargos.clear();

    const auto& freights = freightStorage.getFreights();
    const auto& cargos = cargoStorage.getCargoStorage();
    vector<bool> cargoMatched(cargos.size(), false);

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
