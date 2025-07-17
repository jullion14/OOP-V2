#include <iostream>
#include "FreightStorage.h"
#include "CargoStorage.h"
#include "MatchedStorage.h"

int main() {
    FreightStorage fs;
    CargoStorage   cs;
    MatchedStorage ms;

    fs.loadFreightFromFile("Freight.txt");
    cs.loadCargoFromFile("Cargo.txt");

    ms.generateMatches(fs, cs);
    ms.pruneExpired();
    ms.saveSchedule("schedule.txt", fs, cs);

    std::cout << "schedule.txt generated\n";
    return 0;
}
