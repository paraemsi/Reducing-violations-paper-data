#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    // Nationality of the person who drinks water
    std::string drinksWater;
    // Nationality of the person who owns the zebra
    std::string ownsZebra;
};

// Solve the Zebra Puzzle and return the nationalities for
// the person who drinks water and the person who owns the zebra.
Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
