// done by: Lee Zhi Hong Joseph


// main.cpp
#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>          // for ostringstream
#include <memory>           // for unique_ptr, shared_ptr

#include "CargoStorage.h"
#include "FreightStorage.h"
#include "MatchedStorage.h"
#include "FreightFactory.h"
#include "MiniMoverFactory.h"
#include "CargoCruiserFactory.h"
#include "MegaCarrierFactory.h"
#include "MiniMover.h"
#include "CargoCruiser.h"
#include "MegaCarrier.h"
#include "TimeWindowStrategy.h"

using namespace std;

// forward declarations
void showMainMenu();
int  getUserChoice(int min = 1, int max = 12);

string getFreightType(const shared_ptr<Freight>& f) {
    if (dynamic_cast<MiniMover*>(f.get()))        return "MiniMover";
    else if (dynamic_cast<CargoCruiser*>(f.get())) return "CargoCruiser";
    else if (dynamic_cast<MegaCarrier*>(f.get()))  return "MegaCarrier";
    else                                           return "Unknown";
}

// helper to print cargo + freight side-by-side
void printSideBySide(const CargoStorage& cs,
    const FreightStorage& fs)
{
    const auto& cl = cs.getCargoList();
    const auto& fl = fs.getFreightList();
    size_t rows = max(cl.size(), fl.size());

    cout << left
        << setw(10) << "C_ID"
        << setw(15) << "Destination"
        << setw(8) << "Time"
        << setw(8) << "Group"
        << " | "
        << setw(12) << "F_ID"
        << setw(15) << "Refuel Stop"
        << setw(8) << "Time"
        << setw(14) << "Type"
        << "\n"
        << string(10 + 15 + 8 + 8 + 3 + 12 + 15 + 8 + 14, '-')
        << "\n";

    for (size_t i = 0; i < rows; ++i) {
        // Cargo side
        if (i < cl.size()) {
            auto const& c = cl[i];
            ostringstream cOss;
            cOss << setw(4) << setfill('0') << c->getTime();
            cout << setw(10) << c->getId()
                << setw(15) << c->getLocation()
                << setw(8) << cOss.str()
                << setw(8) << c->getGroupSize();
        }
        else {
            cout << string(10 + 15 + 8 + 8, ' ');
        }

        cout << " | ";

        // Freight side
        if (i < fl.size()) {
            auto const& f = fl[i];
            ostringstream fOss;
            fOss << setw(4) << setfill('0') << f->getTime();
            cout << setw(12) << f->getId()
                << setw(15) << f->getLocation()
                << setw(8) << fOss.str()
                << setw(14) << getFreightType(f);
        }
        cout << "\n";
    }
}

int main() {
    CargoStorage   cs;
    FreightStorage fs;
    MatchedStorage ms;

    // 1) Register all Freight factories
    fs.registerFactory("MiniMover", make_unique<MiniMoverFactory>());
    fs.registerFactory("CargoCruiser", make_unique<CargoCruiserFactory>());
    fs.registerFactory("MegaCarrier", make_unique<MegaCarrierFactory>());

    // 2) Load from files
    cs.loadCargoFromFile("Cargo.txt");
    fs.loadFreightFromFile("Freight.txt");

    bool exitFlag = false;
    while (!exitFlag) {
        showMainMenu();
        int choice = getUserChoice();

        switch (choice) {
        case 1:
            printSideBySide(cs, fs);
            break;

        case 2:
            ms.displaySchedule(fs, cs);
            break;

        case 3: {  // Add Cargo
            auto id = cs.generateNextCargoId();
            cout << "New Cargo ID: " << id << "\n";

            // Require at least one alphabetic character in location
            string loc;
            while (true) {
                cout << "Location: ";
                getline(cin, loc);
                bool hasAlpha = false;
                for (char ch : loc) {
                    if (isalpha(static_cast<unsigned char>(ch))) {
                        hasAlpha = true;
                        break;
                    }
                }
                if (hasAlpha) break;
                cout << "Invalid. Location must contain at least one letter.\n";
            }

            time_t t = 0;
            while (true) {
                cout << "Time (HHMM): ";
                string ts; getline(cin, ts);
                if (ts.size() == 4 && all_of(ts.begin(), ts.end(), ::isdigit)) {
                    int h = stoi(ts.substr(0, 2)), m = stoi(ts.substr(2, 2));
                    if (h < 24 && m < 60) { t = h * 100 + m; break; }
                }
                cout << "Invalid. Try again.\n";
            }

            int g = 0;
            while (true) {
                cout << "Group size (>0): ";
                if (cin >> g && g > 0) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid. Try again.\n";
            }

            cs.addCargo(make_shared<Cargo>(id, loc, t, g));
            cout << "Cargo added in memory.\n";
            break;
        }

        case 4: {  // Edit Cargo
            cout << "Enter Cargo ID to edit: ";
            string id; getline(cin, id);

            cout << "New location: ";
            string loc; getline(cin, loc);

            time_t t = 0;
            while (true) {
                cout << "New time (HHMM): ";
                string ts; getline(cin, ts);
                if (ts.size() == 4 && all_of(ts.begin(), ts.end(), ::isdigit)) {
                    int h = stoi(ts.substr(0, 2)), m = stoi(ts.substr(2, 2));
                    if (h < 24 && m < 60) { t = h * 100 + m; break; }
                }
                cout << "Invalid. Try again.\n";
            }

            int g = 0;
            while (true) {
                cout << "New group size (>0): ";
                if (cin >> g && g > 0) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid. Try again.\n";
            }

            if (cs.editCargo(id, loc, t, g))
                cout << "Cargo updated in memory.\n";
            else
                cout << "Cargo ID not found.\n";
            break;
        }

        case 5: {  // Delete Cargo
            cout << "Enter Cargo ID to delete: ";
            string id; getline(cin, id);
            if (cs.removeCargoById(id))
                cout << "Cargo deleted from memory.\n";
            else
                cout << "Cargo ID not found.\n";
            break;
        }

        case 6: {  // Add Freight
            string id = fs.generateNextFreightId();
            cout << "New Freight ID: " << id << "\n";

            // Require at least one alphabetic character in location
            string loc;
            while (true) {
                cout << "Location: ";
                getline(cin, loc);
                bool hasAlpha = false;
                for (char ch : loc) {
                    if (isalpha(static_cast<unsigned char>(ch))) {
                        hasAlpha = true;
                        break;
                    }
                }
                if (hasAlpha) break;
                cout << "Invalid. Location must contain at least one letter.\n";
            }

            time_t t = 0;
            while (true) {
                cout << "Time (HHMM): ";
                string ts; getline(cin, ts);
                if (ts.size() == 4 && all_of(ts.begin(), ts.end(), ::isdigit)) {
                    int h = stoi(ts.substr(0, 2)), m = stoi(ts.substr(2, 2));
                    if (h < 24 && m < 60) { t = h * 100 + m; break; }
                }
                cout << "Invalid. Try again.\n";
            }

            int ty = 0;
            while (true) {
                cout << "Type (1=MiniMover,2=Cruiser,3=Mega): ";
                if (cin >> ty && ty >= 1 && ty <= 3) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid. Try again.\n";
            }

            string key = (ty == 1 ? "MiniMover"
                : ty == 2 ? "CargoCruiser"
                : "MegaCarrier");
            FreightFactory* fac = fs.getFactory(key);
            if (!fac) {
                cout << "Error: no factory for " << key << "\n";
            }
            else {
                auto f = fac->create(id, loc, t);
                fs.addFreight(f);
                cout << "Freight added in memory.\n";
            }
            break;
        }

        case 7: {  // Edit Freight
            cout << "Enter Freight ID to edit: ";
            string id; getline(cin, id);

            const auto& fl = fs.getFreightList();
            auto it = find_if(fl.begin(), fl.end(),
                [&](auto const& f) { return f->getId() == id; });
            if (it == fl.end()) {
                cout << "Freight ID not found.\n";
                break;
            }

            cout << "New Location: ";
            string loc; getline(cin, loc);

            time_t t = 0;
            while (true) {
                cout << "New Time (HHMM): ";
                string ts; getline(cin, ts);
                if (ts.size() == 4 && all_of(ts.begin(), ts.end(), ::isdigit)) {
                    int h = stoi(ts.substr(0, 2)), m = stoi(ts.substr(2, 2));
                    if (h < 24 && m < 60) { t = h * 100 + m; break; }
                }
                cout << "Invalid. Try again.\n";
            }

            cout << "Change type? 0=keep,1=MiniMover,2=Cruiser,3=Mega: ";
            int ty;
            while (!(cin >> ty) || ty < 0 || ty > 3) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter 0–3: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (ty == 0) {
                fs.editFreight(id, loc, t, 0)
                    ? cout << "Freight updated.\n"
                    : cout << "Freight ID not found.\n";
            }
            else {
                fs.removeFreightById(id);
                string key2 = (ty == 1 ? "MiniMover"
                    : ty == 2 ? "CargoCruiser"
                    : "MegaCarrier");
                FreightFactory* fac2 = fs.getFactory(key2);
                auto newF = fac2->create(id, loc, t);
                fs.addFreight(newF);
                cout << "Freight type & details updated.\n";
            }
            break;
        }

        case 8: {  // Delete Freight
            cout << "Enter Freight ID to delete: ";
            string id; getline(cin, id);

            const auto& fl = fs.getFreightList();
            auto it2 = find_if(fl.begin(), fl.end(),
                [&](auto const& f) { return f->getId() == id; });
            if (it2 == fl.end()) {
                cout << "Freight ID not found.\n";
                break;
            }

            fs.removeFreightById(id);
            cout << "Freight deleted.\n";
            break;
        }

        case 9:
            ms.setStrategy(make_unique<TimeWindowStrategy>(15));
            ms.generateMatches(fs, cs);
            ms.pruneExpired();
            ms.displaySchedule(fs, cs);
            break;

        case 10:  // Save schedule & persist Cargo and Freight
            ms.saveSchedule("schedule.txt", fs, cs);
            cout << "schedule.txt written.\n";
            cs.saveCargoToFile("Cargo.txt");
            fs.saveFreightToFile("Freight.txt");
            cout << "Cargo.txt and Freight.txt updated.\n";
            break;

        case 11:  // Save Cargo & Freight, then exit
            cs.saveCargoToFile("Cargo.txt");
            fs.saveFreightToFile("Freight.txt");
            cout << "Cargo.txt and Freight.txt saved. Exiting.\n";
            exitFlag = true;
            break;

        case 12:  // Exit without saving
            exitFlag = true;
            break;
        }
    }

    return 0;
}

void showMainMenu() {
    cout << "\n===== Main Menu =====\n"
        << " 1) Display Cargo & Freight\n"
        << " 2) Display current schedule\n"
        << " 3) Add Cargo\n"
        << " 4) Edit Cargo\n"
        << " 5) Delete Cargo\n"
        << " 6) Add Freight\n"
        << " 7) Edit Freight\n"
        << " 8) Delete Freight\n"
        << " 9) Generate & view schedule\n"
        << "10) Save schedule to file\n"
        << "11) Save & exit\n"
        << "12) Exit without saving\n"
        << "Select (1-12): ";
}

int getUserChoice(int min, int max) {
    int c;
    while (!(cin >> c) || c < min || c > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter valid option (" << min << "-" << max << "): ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return c;
}
