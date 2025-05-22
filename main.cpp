#include <iostream>
#include <string>
#include <vector>
#include "FreightStorage.h"
#include "CargoStorage.h"
#include "Matcher.h"
#include "MatchedStorage.h"

using namespace std;

int main() {
    FreightStorage freightStorage;
    CargoStorage cargoStorage;
    MatchedStorage matchedStorage;
    vector<string> unmatchedFreights, unmatchedCargos;

    // Load data from files
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
            // Print both Cargo and Freight in a table
            cargoStorage.printCargoTable(freightStorage);
        }
        else if (command == "2") {
            // Display the contents of the schedule file
            matchedStorage.displayScheduleFile("schedule.txt");
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
            matchedStorage.generateMatches(freightStorage, cargoStorage, unmatchedFreights, unmatchedCargos);
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
