#include "FreightStorage.h"
#include "MiniMover.h"
#include "CargoCruiser.h"
#include "MegaCarrier.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

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

        if (type == "MiniMover")
            freights_.push_back(make_shared<MiniMover>(id, loc, t));
        else if (type == "CargoCruiser")
            freights_.push_back(make_shared<CargoCruiser>(id, loc, t));
        else if (type == "MegaCarrier")
            freights_.push_back(make_shared<MegaCarrier>(id, loc, t));
    }
}

void FreightStorage::saveFreightToFile(const string& fn) const {
    ofstream out(fn);
    for (auto const& f : freights_) {
        string type = "Unknown";
        if (dynamic_cast<MiniMover*>(f.get()))      type = "MiniMover";
        else if (dynamic_cast<CargoCruiser*>(f.get()))   type = "CargoCruiser";
        else if (dynamic_cast<MegaCarrier*>(f.get()))    type = "MegaCarrier";

        out << f->getId() << ','
            << f->getLocation() << ','
            << f->getTime() << ','
            << type << "\n";
    }
}

string FreightStorage::generateNextFreightId() const {
    int maxNum = 0;
    for (auto const& f : freights_) {
        string id = f->getId();
        if (id.size() > 1 && id[0] == 'F')
            maxNum = max(maxNum, stoi(id.substr(1)));
    }
    ostringstream oss;
    oss << 'F' << setw(2) << setfill('0') << (maxNum + 1);
    return oss.str();
}

void FreightStorage::addFreight(const shared_ptr<Freight>& freight) {
    freights_.push_back(freight);
}

bool FreightStorage::editFreight(const string& id,
    const string& newLoc,
    time_t         newTime,
    int            newType)
{
    for (size_t i = 0; i < freights_.size(); ++i) {
        auto& f = freights_[i];
        if (f->getId() == id) {
            if (newType == 0) {
                // just update data
                f->setLocation(newLoc);
                f->setTime(newTime);
            }
            else {
                // replace subclass
                shared_ptr<Freight> rep;
                switch (newType) {
                case 1: rep = make_shared<MiniMover>(id, newLoc, newTime); break;
                case 2: rep = make_shared<CargoCruiser>(id, newLoc, newTime); break;
                default:rep = make_shared<MegaCarrier>(id, newLoc, newTime); break;
                }
                freights_[i] = rep;
            }
            return true;
        }
    }
    return false;
}

bool FreightStorage::removeFreightById(const string& id) {
    size_t before = freights_.size();
    freights_.erase(
        remove_if(freights_.begin(), freights_.end(),
            [&](auto const& f) { return f->getId() == id; }),
        freights_.end());
    return freights_.size() != before;
}

void FreightStorage::displayFreight(ostream& out) const {
    out << left
        << setw(12) << "F_ID"
        << setw(15) << "Refuel Stop"
        << setw(8) << "Time"
        << setw(14) << "Type"
        << "\n" << string(12 + 15 + 8 + 14, '-') << "\n";
    for (auto const& f : freights_) {
        string type = "Unknown";
        if (dynamic_cast<MiniMover*>(f.get()))    type = "MiniMover";
        else if (dynamic_cast<CargoCruiser*>(f.get())) type = "CargoCruiser";
        else if (dynamic_cast<MegaCarrier*>(f.get()))  type = "MegaCarrier";

        out << setw(12) << f->getId()
            << setw(15) << f->getLocation()
            << setw(8) << f->getTime()
            << setw(14) << type
            << "\n";
    }
}
