#ifndef FREIGHTSTORAGE_H
#define FREIGHTSTORAGE_H

#include <vector>
#include <memory>
#include <string>
#include <ostream>
#include "Freight.h"
using namespace std;

class FreightStorage {
    vector<shared_ptr<Freight>> freights_;
public:
    // File I/O
    void loadFreightFromFile(const string& filename);
    void saveFreightToFile(const string& filename) const;

    // Access in-memory list
    const vector<shared_ptr<Freight>>& getFreightList() const {
        return freights_;
    }

    // ID generation & CRUD
    string generateNextFreightId() const;
    void   addFreight(const shared_ptr<Freight>& freight);
    bool   editFreight(const string& id,
        const string& newLoc,
        time_t         newTime,
        int            newType);
    bool   removeFreightById(const string& id);

    // Display helper
    void displayFreight(ostream& out = cout) const;
};

#endif // FREIGHTSTORAGE_H
