// main.cpp
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <memory>

#include "FreightStorage.h"
#include "CargoStorage.h"
#include "MatchedStorage.h"
#include "MiniMover.h"
#include "CargoCruiser.h"
#include "MegaCarrier.h"

// Forward declarations
void showMainMenu();
int getUserChoice(int minOption = 1, int maxOption = 11);
std::string generateNextCargoId(const CargoStorage& cs);
std::string generateNextFreightId(const FreightStorage& fs);
std::string getFreightType(const std::shared_ptr<Freight>& f);
void displayCargoAndFreight(const CargoStorage& cs, const FreightStorage& fs);
void displaySchedule();
void addCargo(CargoStorage& cs);
void editCargo(CargoStorage& cs);
void deleteCargo(CargoStorage& cs);
void addFreight(FreightStorage& fs);
void editFreight(FreightStorage& fs);
void deleteFreight(FreightStorage& fs);

int main() {
    FreightStorage fs;
    CargoStorage   cs;
    MatchedStorage ms;

    fs.loadFreightFromFile("Freight.txt");
    cs.loadCargoFromFile("Cargo.txt");

    bool exitFlag = false;
    while (!exitFlag) {
        showMainMenu();
        int choice = getUserChoice();
        switch (choice) {
        case 1: displayCargoAndFreight(cs, fs);      break;
        case 2: displaySchedule();                   break;
        case 3: addCargo(cs);                        break;
        case 4: editCargo(cs);                       break;
        case 5: deleteCargo(cs);                     break;
        case 6: addFreight(fs);                      break;
        case 7: editFreight(fs);                     break;
        case 8: deleteFreight(fs);                   break;
        case 9:
            ms.generateMatches(fs, cs);
            ms.pruneExpired();
            std::cout << "Matched schedule generated in memory.\n";
            break;
        case 10:
            ms.saveSchedule("schedule.txt", fs, cs);
            std::cout << "schedule.txt generated\n";
            break;
        case 11:
            // fs.saveToFile("Freight.txt");
            // cs.saveToFile("Cargo.txt");
            exitFlag = true;
            break;
        }
    }
    return 0;
}

void showMainMenu() {
    std::cout << "\n========== Main Menu ==========\n"
        << " 1. Display Cargo & Freight data\n"
        << " 2. Display current schedule\n"
        << " 3. Add a new Cargo\n"
        << " 4. Edit an existing Cargo\n"
        << " 5. Delete an existing Cargo\n"
        << " 6. Add a new Freight\n"
        << " 7. Edit an existing Freight\n"
        << " 8. Delete an existing Freight\n"
        << " 9. Generate matched schedule\n"
        << "10. Save schedule to file\n"
        << "11. Save & exit\n"
        << "=================================\n"
        << "Select an option (1-11): ";
}

int getUserChoice(int minOption, int maxOption) {
    int choice;
    while (true) {
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a number ("
                << minOption << "-" << maxOption << "): ";
            continue;
        }
        if (choice < minOption || choice > maxOption) {
            std::cout << "Choice out of range. Select ("
                << minOption << "-" << maxOption << "): ";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }
}

std::string generateNextCargoId(const CargoStorage& cs) {
    int maxNum = 0;
    for (const auto& c : cs.getCargoList()) {
        const auto& id = c->getId();
        if (id.size() > 1 && id[0] == 'C') {
            int num = std::stoi(id.substr(1));
            maxNum = std::max(maxNum, num);
        }
    }
    std::ostringstream oss;
    oss << 'C' << std::setw(2) << std::setfill('0') << (maxNum + 1);
    return oss.str();
}

std::string generateNextFreightId(const FreightStorage& fs) {
    int maxNum = 0;
    for (const auto& f : fs.getFreightList()) {
        const auto& id = f->getId();
        if (id.size() > 1 && id[0] == 'F') {
            int num = std::stoi(id.substr(1));
            maxNum = std::max(maxNum, num);
        }
    }
    std::ostringstream oss;
    oss << 'F' << std::setw(2) << std::setfill('0') << (maxNum + 1);
    return oss.str();
}

std::string getFreightType(const std::shared_ptr<Freight>& f) {
    if (!f) return "";
    if (dynamic_cast<MiniMover*>(f.get()))    return "MiniMover";
    if (dynamic_cast<CargoCruiser*>(f.get())) return "CargoCruiser";
    if (dynamic_cast<MegaCarrier*>(f.get()))  return "MegaCarrier";
    return "Unknown";
}

void displayCargoAndFreight(const CargoStorage& cs, const FreightStorage& fs) {
    const auto& cargoList = cs.getCargoList();
    const auto& freightList = fs.getFreightList();
    size_t maxRows = std::max(cargoList.size(), freightList.size());

    std::cout << std::left
        << std::setw(12) << "C_ID"
        << std::setw(12) << "C_Loc"
        << std::setw(12) << "C_Time"
        << std::setw(8) << "Group"
        << " | "
        << std::setw(12) << "F_ID"
        << std::setw(12) << "F_Loc"
        << std::setw(12) << "F_Time"
        << std::setw(12) << "Type"
        << "\n" << std::string(95, '-') << "\n";

    for (size_t i = 0; i < maxRows; ++i) {
        if (i < cargoList.size()) {
            auto c = cargoList[i];
            std::cout << std::setw(12) << c->getId()
                << std::setw(12) << c->getLocation()
                << std::setw(12) << c->getTime()
                << std::setw(8) << c->getGroupSize();
        }
        else {
            std::cout << std::string(44, ' ');
        }
        std::cout << " | ";
        if (i < freightList.size()) {
            auto f = freightList[i];
            std::cout << std::setw(12) << f->getId()
                << std::setw(12) << f->getLocation()
                << std::setw(12) << f->getTime()
                << std::setw(12) << getFreightType(f);
        }
        std::cout << "\n";
    }
}

void displaySchedule() {
    std::ifstream inFile("schedule.txt");
    if (!inFile) {
        std::cout << "No schedule.txt found. Generate it first.\n";
        return;
    }
    std::string line;
    while (std::getline(inFile, line))
        std::cout << line << "\n";
}

void addCargo(CargoStorage& cs) {
    std::string id = generateNextCargoId(cs);
    std::cout << "Generated Cargo ID: " << id << "\n";

    std::cout << "Enter location: ";
    std::string loc; std::getline(std::cin, loc);

    time_t t = 0;
    while (true) {
        std::cout << "Enter time (HHMM): ";
        std::string ts; std::getline(std::cin, ts);
        if (ts.size() != 4 || !std::all_of(ts.begin(), ts.end(), ::isdigit)) {
            std::cout << " Invalid format.\n";
            continue;
        }
        int h = std::stoi(ts.substr(0, 2));
        int m = std::stoi(ts.substr(2, 2));
        if (h < 0 || h>23 || m < 0 || m>59) {
            std::cout << " Hour/min out of range.\n";
            continue;
        }
        t = h * 100 + m;
        break;
    }

    int group;
    while (true) {
        std::cout << "Enter group size (>0): ";
        if (!(std::cin >> group) || group <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << " Invalid size.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }

    cs.addCargo(std::make_shared<Cargo>(id, loc, t, group));
    std::cout << "Cargo added in memory.\n";
}

void editCargo(CargoStorage& cs) {
    std::cout << "Enter Cargo ID to edit: ";
    std::string id; std::getline(std::cin, id);

    auto& list = const_cast<std::vector<std::shared_ptr<Cargo>>&>(cs.getCargoList());
    auto it = std::find_if(list.begin(), list.end(),
        [&](const std::shared_ptr<Cargo>& c) { return c->getId() == id; });
    if (it == list.end()) {
        std::cout << "Cargo ID not found.\n";
        return;
    }
    auto cargo = *it;

    std::cout << "Current location: " << cargo->getLocation() << "\nEnter new location: ";
    std::string loc; std::getline(std::cin, loc);
    cargo->setLocation(loc);

    time_t t = 0;
    while (true) {
        std::cout << "Current time: " << cargo->getTime() << "\nEnter new time (HHMM): ";
        std::string ts; std::getline(std::cin, ts);
        if (ts.size() != 4 || !std::all_of(ts.begin(), ts.end(), ::isdigit)) {
            std::cout << " Invalid format.\n";
            continue;
        }
        int h = std::stoi(ts.substr(0, 2));
        int m = std::stoi(ts.substr(2, 2));
        if (h < 0 || h>23 || m < 0 || m>59) {
            std::cout << " Hour/min out of range.\n";
            continue;
        }
        t = h * 100 + m;
        break;
    }
    cargo->setTime(t);

    int g;
    while (true) {
        std::cout << "Current group: " << cargo->getGroupSize() << "\nEnter new group size: ";
        if (!(std::cin >> g) || g <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << " Invalid size.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
    cargo->setGroupSize(g);

    std::cout << "Cargo updated in memory.\n";
}

void deleteCargo(CargoStorage& cs) {
    std::cout << "Enter Cargo ID to delete: ";
    std::string id; std::getline(std::cin, id);

    if (cs.removeCargoById(id))
        std::cout << "Cargo \"" << id << "\" deleted in memory.\n";
    else
        std::cout << "Cargo ID not found. No deletion performed.\n";
}

void addFreight(FreightStorage& fs) {
    std::string id = generateNextFreightId(fs);
    std::cout << "Generated Freight ID: " << id << "\n";

    std::cout << "Enter location: ";
    std::string loc; std::getline(std::cin, loc);

    time_t t = 0;
    while (true) {
        std::cout << "Enter time (HHMM): ";
        std::string ts; std::getline(std::cin, ts);
        if (ts.size() != 4 || !std::all_of(ts.begin(), ts.end(), ::isdigit)) {
            std::cout << " Invalid format.\n";
            continue;
        }
        int h = std::stoi(ts.substr(0, 2));
        int m = std::stoi(ts.substr(2, 2));
        if (h < 0 || h>23 || m < 0 || m>59) {
            std::cout << " Hour/min out of range.\n";
            continue;
        }
        t = h * 100 + m;
        break;
    }

    std::cout << "Select type: 1.MiniMover 2.CargoCruiser 3.MegaCarrier: ";
    int ty;
    while (!(std::cin >> ty) || ty < 1 || ty > 3) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << " Enter 1-3: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::shared_ptr<Freight> ptr;
    if (ty == 1)      ptr = std::make_shared<MiniMover>(id, loc, t);
    else if (ty == 2) ptr = std::make_shared<CargoCruiser>(id, loc, t);
    else              ptr = std::make_shared<MegaCarrier>(id, loc, t);

    fs.addFreight(ptr);
    std::cout << "Freight added in memory.\n";
}

void editFreight(FreightStorage& fs) {
    std::cout << "Enter Freight ID to edit: ";
    std::string id; std::getline(std::cin, id);

    auto& vec = const_cast<std::vector<std::shared_ptr<Freight>>&>(fs.getFreightList());
    auto it = std::find_if(vec.begin(), vec.end(),
        [&](const std::shared_ptr<Freight>& f) { return f->getId() == id; });
    if (it == vec.end()) {
        std::cout << "Freight ID not found.\n";
        return;
    }
    size_t idx = std::distance(vec.begin(), it);
    auto freight = *it;

    // Edit location
    std::cout << "Current location: " << freight->getLocation()
        << "\nEnter new location: ";
    std::string loc; std::getline(std::cin, loc);
    freight->setLocation(loc);

    // Edit time
    time_t t = 0;
    while (true) {
        std::cout << "Current time: " << freight->getTime()
            << "\nEnter new time (HHMM): ";
        std::string ts; std::getline(std::cin, ts);
        if (ts.size() != 4 || !std::all_of(ts.begin(), ts.end(), ::isdigit)) {
            std::cout << " Invalid format.\n";
            continue;
        }
        int h = std::stoi(ts.substr(0, 2));
        int m = std::stoi(ts.substr(2, 2));
        if (h < 0 || h>23 || m < 0 || m>59) {
            std::cout << " Hour/min out of range.\n";
            continue;
        }
        t = h * 100 + m;
        break;
    }
    freight->setTime(t);

    // Change type?
    std::cout << "Current type: " << getFreightType(freight)
        << "\nChoose new type or 0 to keep:\n"
        << " 0. No change\n"
        << " 1. MiniMover\n"
        << " 2. CargoCruiser\n"
        << " 3. MegaCarrier\n"
        << "Selection: ";
    int ty;
    while (!(std::cin >> ty) || ty < 0 || ty > 3) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << " Enter 0–3: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (ty != 0) {
        std::shared_ptr<Freight> replacement;
        if (ty == 1)      replacement = std::make_shared<MiniMover>(id, loc, t);
        else if (ty == 2) replacement = std::make_shared<CargoCruiser>(id, loc, t);
        else              replacement = std::make_shared<MegaCarrier>(id, loc, t);
        vec[idx] = replacement;
        std::cout << "Freight type changed to " << getFreightType(replacement) << ".\n";
    }
    else {
        std::cout << "Freight type unchanged.\n";
    }

    std::cout << "Freight updated in memory.\n";
}

void deleteFreight(FreightStorage& fs) {
    std::cout << "Enter Freight ID to delete: ";
    std::string id; std::getline(std::cin, id);

    if (fs.removeFreightById(id))
        std::cout << "Freight \"" << id << "\" deleted in memory.\n";
    else
        std::cout << "Freight ID not found. No deletion performed.\n";
}
