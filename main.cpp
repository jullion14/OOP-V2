#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include "FreightStorage.h"
#include "CargoStorage.h"
#include "Matcher.h"
#include "MatchedStorage.h"

using namespace std;

// Table display for both Cargo and Freight, side by side
void printCargoAndFreightTable(const CargoStorage& cargoStorage, const FreightStorage& freightStorage) {
    const auto& cargos = cargoStorage.getCargoStorage();
    const auto& freights = freightStorage.getFreights();
    size_t maxRows = max(cargos.size(), freights.size());

    // Headers
    cout << left << setw(10) << "Cargo ID"
        << setw(16) << "Destination"
        << setw(8) << "Time"
        << "    "
        << setw(12) << "Freight ID"
        << setw(16) << "Refuel Stop"
        << setw(12) << "Refuel Time" << endl;

    // Separators
    cout << string(34, '=') << "    " << string(40, '=') << endl;

    // Rows
    for (size_t i = 0; i < maxRows; ++i) {
        // Cargo columns
        if (i < cargos.size()) {
            cout << left << setw(10) << cargos[i].getCid()
                << setw(16) << cargos[i].getClocation()
                << setw(8) << setfill('0') << setw(4) << cargos[i].getCtime() << setfill(' ');
        }
        else {
            cout << setw(10) << "" << setw(16) << "" << setw(8) << "";
        }

        cout << "    "; // gap between tables

        // Freight columns
        if (i < freights.size()) {
            cout << left << setw(12) << freights[i].getFid()
                << setw(16) << freights[i].getFlocation()
                << setw(12) << setfill('0') << setw(4) << freights[i].getFtime() << setfill(' ');
        }
        else {
            cout << setw(12) << "" << setw(16) << "" << setw(12) << "";
        }
        cout << endl;
    }
}

// Simple matching: match by location and time
void generateMatches(const FreightStorage& freightStorage, const CargoStorage& cargoStorage,
    MatchedStorage& matchedStorage, vector<string>& unmatchedFreights, vector<string>& unmatchedCargos) {
    matchedStorage = MatchedStorage(); // Clear previous matches
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
                matchedStorage.addMatch(match);
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

int main() {
    FreightStorage freightStorage;
    CargoStorage cargoStorage;
    MatchedStorage matchedStorage;
    vector<string> unmatchedFreights, unmatchedCargos;

    // Load data from current directory
    freightStorage.loadFreightFromFile("Freight.txt");
    cargoStorage.loadCargoFromFile("Cargo.txt");

    string command;

    cout << "========== MAIN MENU ==========" << endl;
    while (true) {
        cout << "\n1. View Cargo\n"
            << "2. View Schedule\n"
            << "3. Add Cargo\n"
            << "4. Edit Cargo\n"
            << "5. Delete Cargo\n"
            << "6. Add Freight\n"
            << "7. Edit Freight\n"
            << "8. Delete Freight\n"
            << "9. Generate & View Schedule\n"
            << "10. Save Schedule to File\n"
            << "11. Exit\n"
            << "Select an option: ";
        getline(cin, command);

        if (command == "1") {
            printCargoAndFreightTable(cargoStorage, freightStorage);
        }
        else if (command == "2") {
            matchedStorage.displayAllMatches();
        }
        else if (command == "3") {
            string id, location, timeStr;
            time_t timeVal;
            cout << "Enter Cargo ID: ";
            getline(cin, id);
            cout << "Enter Location: ";
            getline(cin, location);
            cout << "Enter Time (as integer, e.g. 900 for 9am): ";
            getline(cin, timeStr);
            timeVal = stoi(timeStr);
            Cargo c(id, location, timeVal);
            cargoStorage.addCargo(c);
            cout << "Cargo added.\n";
        }
        else if (command == "4") {
            string id, location, timeStr;
            time_t timeVal;
            cout << "Enter Cargo ID to edit: ";
            getline(cin, id);
            cout << "Enter New Location: ";
            getline(cin, location);
            cout << "Enter New Time (as integer): ";
            getline(cin, timeStr);
            timeVal = stoi(timeStr);
            if (cargoStorage.editCargo(id, location, timeVal)) {
                cout << "Cargo updated.\n";
            }
            else {
                cout << "Cargo not found.\n";
            }
        }
        else if (command == "5") {
            string id;
            cout << "Enter Cargo ID to delete: ";
            getline(cin, id);
            if (cargoStorage.deleteCargo(id)) {
                cout << "Cargo deleted.\n";
            }
            else {
                cout << "Cargo not found.\n";
            }
        }
        else if (command == "6") {
            string id, location, timeStr;
            time_t timeVal;
            cout << "Enter Freight ID: ";
            getline(cin, id);
            cout << "Enter Location: ";
            getline(cin, location);
            cout << "Enter Time (as integer, e.g. 900 for 9am): ";
            getline(cin, timeStr);
            timeVal = stoi(timeStr);
            Freight f(id, location, timeVal);
            freightStorage.addFreight(f);
            cout << "Freight added.\n";
        }
        else if (command == "7") {
            string id, location, timeStr;
            time_t timeVal;
            cout << "Enter Freight ID to edit: ";
            getline(cin, id);
            cout << "Enter New Location: ";
            getline(cin, location);
            cout << "Enter New Time (as integer): ";
            getline(cin, timeStr);
            timeVal = stoi(timeStr);
            if (freightStorage.editFreight(id, location, timeVal)) {
                cout << "Freight updated.\n";
            }
            else {
                cout << "Freight not found.\n";
            }
        }
        else if (command == "8") {
            string id;
            cout << "Enter Freight ID to delete: ";
            getline(cin, id);
            if (freightStorage.deleteFreight(id)) {
                cout << "Freight deleted.\n";
            }
            else {
                cout << "Freight not found.\n";
            }
        }
        else if (command == "9") {
            generateMatches(freightStorage, cargoStorage, matchedStorage, unmatchedFreights, unmatchedCargos);
            matchedStorage.displayAllMatches();
            cout << "\nUnmatched Freights:\n";
            for (const auto& fid : unmatchedFreights) cout << fid << endl;
            cout << "\nUnmatched Cargos:\n";
            for (const auto& cid : unmatchedCargos) cout << cid << endl;
        }
        else if (command == "10") {
            string filename;
            cout << "Enter filename to save schedule (e.g., schedule.txt): ";
            getline(cin, filename);
            matchedStorage.saveMatches(filename);
        }
        else if (command == "11") {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
