// done by: Loh Kaize Kaiser

#ifndef MATCHEDSTORAGE_H
#define MATCHEDSTORAGE_H

#include <vector>
#include <string>
#include <memory>
#include "Matcher.h"
#include "FreightStorage.h"
#include "CargoStorage.h"
#include "MatchStrategy.h"

/**
 * @class MatchedStorage
 * @brief Handles the pairing of Freight and Cargo, using a matching strategy.
 *
 * Stores all currently matched pairs, allows switching the matching logic,
 * and provides functionality to save/display the match schedule.
 */
class MatchedStorage {
    std::vector<Matcher> matchedList_;            ///< All current matches.
    std::unique_ptr<MatchStrategy> strategy_;     ///< Matching rule in use.

public:
    /**
     * @brief Set the algorithm/strategy used for matching.
     * @param s Unique pointer to a MatchStrategy implementation.
     */
    void setStrategy(std::unique_ptr<MatchStrategy> s) {
        strategy_ = std::move(s);
    }

    /**
     * @brief Pair cargoes with freights according to the current strategy.
     * @param fs Reference to FreightStorage.
     * @param cs Reference to CargoStorage.
     */
    void generateMatches(const FreightStorage& fs,
        const CargoStorage& cs);

    /**
     * @brief Remove matches whose cargo or freight have expired.
     */
    void pruneExpired();

    /**
     * @brief Save current schedule (matches and unmatched) to a file.
     * @param filename Output filename.
     * @param fs Freight storage reference.
     * @param cs Cargo storage reference.
     */
    void saveSchedule(const std::string& filename,
        const FreightStorage& fs,
        const CargoStorage& cs) const;

    /**
     * @brief Print matched and unmatched entries to the console.
     * @param fs Freight storage reference.
     * @param cs Cargo storage reference.
     */
    void displaySchedule(const FreightStorage& fs,
        const CargoStorage& cs) const;
};

#endif // MATCHEDSTORAGE_H
