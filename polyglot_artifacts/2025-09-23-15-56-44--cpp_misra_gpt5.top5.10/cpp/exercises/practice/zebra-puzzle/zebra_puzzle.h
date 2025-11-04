#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

// Holds the names of the residents for water drinker and zebra owner.
// Field names must remain 'drinksWater' and 'ownsZebra' to satisfy tests.
struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

// Solve the zebra puzzle and return the names for:
// - who drinks water
// - who owns the zebra
Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
