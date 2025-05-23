#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include "FreightStorage.h"
#include "CargoStorage.h"
#include "Matcher.h"
#include "MatchedStorage.h"

using namespace std;

// Helper: Validate 24-hour time input
time_t getValidatedTime() {
    string input;
    int time = 0;

    while (true) {
        cout << "Enter Time (e.g. 0900 for 9am): ";
        getline(cin, input);

        if (input.empty() || !all_of(input.begin(), input.end(), ::isdigit)) {
            cout << "Invalid input: Enter numbers only.\n";
            continue;
        }

        try {
            time = stoi(input);
            if (time >= 0 && time <= 2359 && time % 100 < 60)
                return time;
            else
                cout << "Invalid time: Must be in 24-hour format (0000 to 2359).\n";
        }
        catch (...) {
            cout << "Error converting time.\n";
        }
    }
}

// Helper: Validate letters-only location
string getValidatedLocation() {
    string location;
    while (true) {
        cout << "Enter Location: ";
        getline(cin, location);

        if (!location.empty() && all_of(location.begin(), location.end(), [](char c) {
            return isalpha(c) || isspace(c);
            })) {
            return location;
        }
        else {
            cout << "Invalid location: Letters and spaces only.\n";
        }
    }
}

int main() {
    FreightStorage freightStorage;
    CargoStorage cargoStorage;
    MatchedStorage matchedStorage;
    vector<string> unmatchedFreights, unmatchedCargos;

    freightStorage.loadFreightFromFile("Freight.txt");
    cargoStorage.loadCargoFromFile("Cargo.txt");

    string command;
    int option;

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

        try {
            option = stoi(command);
        }
        catch (...) {
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (option) {
        case 1:
            cargoStorage.printCargoTable(freightStorage);
            break;

        case 2:
            matchedStorage.displayScheduleFile("schedule.txt");
            break;

        case 3: {
            string id = cargoStorage.generateNextCargoId();
            cout << "Auto-generated Cargo ID: " << id << endl;


            string location = getValidatedLocation();
            time_t time = getValidatedTime();

            try {
                Cargo c(id, location, time);
                cargoStorage.addCargo(c);
            }
            catch (const exception& e) {
                cout << "Error adding cargo: " << e.what() << endl;
            }
            break;
        }

        case 4: {
            string id;

            while (true) {
                cout << "Enter Cargo ID to edit (blank = cancel): ";
                getline(cin, id);

                if (id.empty()) break;                    // leave loop then cancel
                if (cargoStorage.exists(id)) break;       // found then continue below

                cout << "Cargo not found. Try again.\n";
            }
            if (id.empty()) {                             // cancelled
                cout << "No ID entered - returning to main menu.\n";
                break;
            }

            string location = getValidatedLocation();
            time_t timeVal = getValidatedTime();

            if (cargoStorage.editCargo(id, location, timeVal))
                cout << "Cargo updated.\n";
            else
                cout << "Update failed (data invalid).\n";
            break;
        }


        case 5: {
            string id;
            do {
                cout << "Enter Cargo ID to delete: ";
                getline(cin, id);
                if (id.empty()) {
                    cout << "Cargo ID cannot be empty. Please try again.\n";
                }
            } while (id.empty());

            if (!cargoStorage.exists(id)) {
                cout << "Cargo not found.\n";
                break;
            }

            string confirm;
            do {
                cout << "Are you sure you want to delete Cargo " << id << "? (Y/N): ";
                getline(cin, confirm);
                if (!confirm.empty()) {
                    confirm[0] = tolower(confirm[0]);
                }
            } while (confirm != "y" && confirm != "n");

            if (confirm == "y") {
                if (cargoStorage.deleteCargo(id))
                    cout << "Cargo deleted.\n";
                else
                    cout << "Failed to delete cargo.\n";
            }
            else {
                cout << "Deletion cancelled.\n";
            }
            break;
        }

        case 6: {
            string id = freightStorage.generateNextFreightId();
            cout << "Auto-generated Freight ID: " << id << endl;

            string location = getValidatedLocation();
            time_t time = getValidatedTime();

            try {
                Freight f(id, location, time);
                freightStorage.addFreight(f);
            }
            catch (const exception& e) {
                cout << "Error adding freight: " << e.what() << endl;
            }
            break;
        }

        case 7: {
            string id;

            while (true) {
                cout << "Enter Freight ID to edit (blank = cancel): ";
                getline(cin, id);

                if (id.empty()) break;
                if (freightStorage.exists(id)) break;

                cout << "Freight not found. Try again.\n";
            }
            if (id.empty()) {
                cout << "No ID entered - returning to main menu.\n";
                break;
            }

            string location = getValidatedLocation();
            time_t timeVal = getValidatedTime();

            if (freightStorage.editFreight(id, location, timeVal))
                cout << "Freight updated.\n";
            else
                cout << "Update failed (data invalid).\n";
            break;
        }

        case 8: {
            string id;
            do {
                cout << "Enter Freight ID to delete: ";
                getline(cin, id);
                if (id.empty()) {
                    cout << "Freight ID cannot be empty. Please try again.\n";
                }
            } while (id.empty());

            if (!freightStorage.exists(id)) {
                cout << "Freight not found.\n";
                break;
            }

            string confirm;
            do {
                cout << "Are you sure you want to delete Freight " << id << "? (Y/N): ";
                getline(cin, confirm);
                if (!confirm.empty()) {
                    confirm[0] = tolower(confirm[0]);
                }
            } while (confirm != "y" && confirm != "n");

            if (confirm == "y") {
                if (freightStorage.deleteFreight(id))
                    cout << "Freight deleted.\n";
                else
                    cout << "Failed to delete freight.\n";
            }
            else {
                cout << "Deletion cancelled.\n";
            }
            break;
        }

        case 9: {
            matchedStorage.generateMatches(freightStorage, cargoStorage, unmatchedFreights, unmatchedCargos);
            matchedStorage.displayAllMatches(unmatchedFreights, unmatchedCargos);
            break;
        }

        case 10: {
            string filename;
            matchedStorage.saveMatches("schedule.txt", unmatchedFreights, unmatchedCargos);
            break;
        }

        case 11: {
            string choice;
            cout << "\nDo you want to save changes to Cargo.txt and Freight.txt? (Y/N): ";
            getline(cin, choice);

            if (choice == "Y" || choice == "y") {
                cargoStorage.saveCargoStorage("Cargo.txt");
                freightStorage.saveFreightStorage("Freight.txt");
                cout << "Changes saved.\n";
            }
            else {
                cout << "Changes not saved.\n";
            }

            cout << "Exiting...\n";
            return 0;
        }


        default:
            cout << "Invalid option. Try again.\n";
            break;
        }
    }

    return 0;
}
