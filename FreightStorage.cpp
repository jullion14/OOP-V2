#include "FreightStorage.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

FreightStorage::FreightStorage() {}

void FreightStorage::loadFreightFromFile(const string& filename) {
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
                Freight freight(id, location, timeVal);  // Constructor handles assignment
                addFreight(freight);
            }
            catch (const exception& e) {
                cout << "Invalid freight data: " << e.what() << " Line: " << line << endl;
            }
        }
    }

    infile.close();
}

void FreightStorage::addFreight(const Freight& freight) {
    freights.push_back(freight);
    // cout << "Added Freight: " << freight.getFid() << endl;
}

bool FreightStorage::editFreight(const string& id, const string& newLocation, time_t newTime) {
    for (auto& f : freights) {
        string fid = f.getFid();
        string uid = id;
        transform(fid.begin(), fid.end(), fid.begin(), ::toupper);
        transform(uid.begin(), uid.end(), uid.begin(), ::toupper);

        if (fid == uid) {                     // case-insensitive match
            try {
                f.setFlocation(newLocation);
                f.setFtime(newTime);
            }
            catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
                return false;
            }
            cout << "Edited Freight: " << f.getFid() << endl;
            return true;
        }
    }
    cout << "Freight not found: " << id << endl;
    return false;
}

bool FreightStorage::deleteFreight(const std::string& id)
{
    std::string query = id;
    std::transform(query.begin(), query.end(), query.begin(), ::toupper);

    auto it = std::remove_if(freights.begin(), freights.end(),
        [&](const Freight& f)
        {
            std::string fid = f.getFid();
            std::transform(fid.begin(), fid.end(), fid.begin(), ::toupper);
            return fid == query;                // case-insensitive match
        });

    if (it != freights.end()) {
        freights.erase(it, freights.end());
        return true;
    }
    return false;
}

void FreightStorage::saveFreightStorage(const string& filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cout << "Error: Could not open " << filename << " for writing.\n";
        return;
    }

    for (const auto& f : freights) {
        ofs << f.getFid() << "," << f.getFlocation() << "," << f.getFtime() << "\n";
    }

    ofs.close();
    cout << "Freight data saved to " << filename << endl;
}


const vector<Freight>& FreightStorage::getFreights() const {
    return freights;
}

std::string FreightStorage::generateNextFreightId() const {
    if (freights.empty()) return "F1";

    const string& lastId = freights.back().getFid(); // e.g., "F8"
    int number = stoi(lastId.substr(1));
    return "F" + to_string(number + 1);
}

bool FreightStorage::exists(const string& id) const {
    string query = id;
    transform(query.begin(), query.end(), query.begin(), ::toupper);

    for (const auto& f : freights) {
        string fid = f.getFid();
        transform(fid.begin(), fid.end(), fid.begin(), ::toupper);
        if (fid == query)
            return true;
    }
    return false;
}