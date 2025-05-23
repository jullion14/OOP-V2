#include "CargoStorage.h"
#include "FreightStorage.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

CargoStorage::CargoStorage() {}

void CargoStorage::loadCargoFromFile(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cout << "Cannot open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string id, location, timeStr;
        if (getline(ss, id, ',') && getline(ss, location, ',') && getline(ss, timeStr)) {
            try {
                time_t timeVal = stoi(timeStr);
                Cargo cargo(id, location, timeVal); // Validation happens here
                cargos.push_back(cargo);
            }
            catch (const exception& e) {
                cout << "Invalid cargo data: " << e.what() << " Line: " << line << endl;
            }
        }
    }

    infile.close();
}

void CargoStorage::addCargo(const Cargo& cargo) {
    cargos.push_back(cargo); // Assume validation already done by caller
}

bool CargoStorage::editCargo(const string& id, const string& newLocation, time_t newTime) {
    for (auto& c : cargos) {
        string cid = c.getCid();
        string uid = id;
        transform(cid.begin(), cid.end(), cid.begin(), ::toupper);
        transform(uid.begin(), uid.end(), uid.begin(), ::toupper);

        if (cid == uid) {                     // case-insensitive match
            try {
                c.setClocation(newLocation);
                c.setCtime(newTime);
            }
            catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
                return false;
            }
            cout << "Edited Cargo: " << c.getCid() << endl;
            return true;
        }
    }
    cout << "Cargo not found: " << id << endl;
    return false;
}

bool CargoStorage::deleteCargo(const string& id) {
    auto it = remove_if(cargos.begin(), cargos.end(),
        [&id](const Cargo& c) { return c.getCid() == id; });

    if (it != cargos.end()) {
        cargos.erase(it, cargos.end());
        cout << "Deleted Cargo: " << id << endl;
        return true;
    }

    cout << "Cargo not found: " << id << endl;
    return false;
}

void CargoStorage::saveCargoStorage(const string& filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cout << "Error: Could not open " << filename << " for writing.\n";
        return;
    }

    for (const auto& c : cargos) {
        ofs << c.getCid() << "," << c.getClocation() << "," << c.getCtime() << "\n";
    }

    ofs.close();
    cout << "Cargo data saved to " << filename << endl;
}


const vector<Cargo>& CargoStorage::getCargoStorage() const {
    return cargos;
}

void CargoStorage::printCargoTable(const FreightStorage& freightStorage) const {
    const auto& freights = freightStorage.getFreights();
    size_t maxRows = max(cargos.size(), freights.size());

    // Header
    cout << left << setw(10) << "Cargo ID"
        << setw(20) << "Destination"
        << setw(8) << "Time"
        << "    "
        << setw(12) << "Freight ID"
        << setw(20) << "Refuel Stop"
        << setw(12) << "Refuel Time" << endl;

    // Divider
    cout << string(38, '=') << "    " << string(44, '=') << endl;

    // Rows
    for (size_t i = 0; i < maxRows; ++i) {
        // --- Cargo section ---
        if (i < cargos.size()) {
            cout << left << setw(10) << cargos[i].getCid()
                << setw(20) << cargos[i].getClocation();

            // Print zero-padded 4-digit time inside an 8-char column
            ostringstream cargoTime;
            cargoTime << setfill('0') << setw(4) << cargos[i].getCtime();
            cout << setw(8) << cargoTime.str();
        }
        else {
            cout << setw(10) << "" << setw(20) << "" << setw(8) << "";
        }

        cout << "    ";

        // --- Freight section ---
        if (i < freights.size()) {
            cout << left << setw(12) << freights[i].getFid()
                << setw(20) << freights[i].getFlocation();

            // Print zero-padded 4-digit time inside a 12-char column
            ostringstream freightTime;
            freightTime << setfill('0') << setw(4) << freights[i].getFtime();
            cout << setw(12) << freightTime.str();
        }
        else {
            cout << setw(12) << "" << setw(20) << "" << setw(12) << "";
        }

        cout << endl;
    }
}

string CargoStorage::generateNextCargoId() const {
    if (cargos.empty()) return "C1";

    const string& lastId = cargos.back().getCid(); // e.g., "C9"
    int number = stoi(lastId.substr(1));           // remove 'C' and convert to int
    return "C" + to_string(number + 1);             // e.g., C10
}

bool CargoStorage::exists(const string& id) const {
    string query = id;
    transform(query.begin(), query.end(), query.begin(), ::toupper);

    for (const auto& c : cargos) {
        string cid = c.getCid();
        transform(cid.begin(), cid.end(), cid.begin(), ::toupper);
        if (cid == query)
            return true;
    }
    return false;
}

