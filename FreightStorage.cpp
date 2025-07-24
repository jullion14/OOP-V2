// done by: Lim Ding Huang Jonas

// FreightStorage.cpp
#include "FreightStorage.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

/**
 * @brief Register a new freight factory with a type key.
 * @param type String type identifier (e.g., "MiniMover").
 * @param factory Unique pointer to the FreightFactory implementation.
 */
void FreightStorage::registerFactory(const string& type,
    unique_ptr<FreightFactory> factory)
{
    factories_[type] = move(factory);
}

/**
 * @brief Load all freight records from a CSV file.
 * @param fn Input file path.
 */
void FreightStorage::loadFreightFromFile(const string& fn) {
    ifstream in(fn);
    if (!in) return;
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, loc, tstr, type;
        if (!getline(ss, id, ','))   continue;
        if (!getline(ss, loc, ','))  continue;
        if (!getline(ss, tstr, ',')) continue;
        if (!getline(ss, type, ',')) continue;
        time_t t = static_cast<time_t>(stoll(tstr));

        auto it = factories_.find(type);
        if (it != factories_.end()) {
            freights_.push_back(it->second->create(id, loc, t));
        }
        // else: unknown type ? skip or log
    }
}

/**
 * @brief Save all freight records to a CSV file.
 * @param fn Output file path.
 */
void FreightStorage::saveFreightToFile(const string& fn) const {
    ofstream out(fn);
    for (auto const& f : freights_) {
        out << f->getId() << ','
            << f->getLocation() << ','
            << f->getTime() << ','
            << f->typeName() << "\n";
    }
}

/**
 * @brief Generate the next unique freight ID (e.g., F01, F02...).
 * @return String of the next available ID.
 */
string FreightStorage::generateNextFreightId() const {
    int maxNum = 0;
    for (auto const& f : freights_) {
        auto id = f->getId();
        if (id.size() > 1 && id[0] == 'F')
            maxNum = max(maxNum, stoi(id.substr(1)));
    }
    ostringstream oss;
    oss << 'F' << setw(2) << setfill('0') << (maxNum + 1);
    return oss.str();
}

/**
 * @brief Add a new Freight object to memory.
 * @param freight Shared pointer to Freight to add.
 */
void FreightStorage::addFreight(const shared_ptr<Freight>& freight) {
    freights_.push_back(freight);
}

/**
 * @brief Edit an existing freight record (by ID).
 * @param id       ID of the freight to modify.
 * @param newLoc   New location.
 * @param newTime  New available time.
 * @param newType  New type as int (0=keep type, 1=MiniMover, 2=Cruiser, 3=MegaCarrier).
 * @return true if update succeeded, false otherwise.
 */
bool FreightStorage::editFreight(const string& id,
    const string& newLoc,
    time_t         newTime,
    int            newType)
{
    for (auto& f : freights_) {
        if (f->getId() == id) {
            if (newType == 0) {
                f->setLocation(newLoc);
                f->setTime(newTime);
            }
            else {
                // Convert type int to type string key
                string key = (newType == 1 ? "MiniMover"
                    : newType == 2 ? "CargoCruiser"
                    : "MegaCarrier");
                auto it = factories_.find(key);
                if (it != factories_.end()) {
                    f = it->second->create(id, newLoc, newTime);
                }
            }
            return true;
        }
    }
    return false;
}

/**
 * @brief Remove a freight record by ID.
 * @param id ID to remove.
 * @return true if removed, false otherwise.
 */
bool FreightStorage::removeFreightById(const string& id) {
    auto before = freights_.size();
    freights_.erase(
        remove_if(freights_.begin(), freights_.end(),
            [&](auto const& f) { return f->getId() == id; }),
        freights_.end());
    return freights_.size() != before;
}

/**
 * @brief Print all freight records in a formatted table.
 * @param out Output stream (default: std::cout).
 */
void FreightStorage::displayFreight(ostream& out) const {
    out << left
        << setw(12) << "F_ID"
        << setw(15) << "Location"
        << setw(8) << "Time"
        << setw(14) << "Type"
        << "\n" << string(49, '-') << "\n";

    for (auto const& f : freights_) {
        out << setw(12) << f->getId()
            << setw(15) << f->getLocation()
            << setw(8) << f->getTime()
            << setw(14) << f->typeName()
            << "\n";
    }
}
