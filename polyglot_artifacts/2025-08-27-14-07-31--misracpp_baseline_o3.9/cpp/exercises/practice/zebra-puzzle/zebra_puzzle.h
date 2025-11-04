#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

/**
 * Solve the classic Zebra Puzzle.
 *
 * Returns a `Solution` struct where:
 *  - `drinksWater` holds the nationality of the person who drinks water
 *  - `ownsZebra`  holds the nationality of the person who owns the zebra
 */
Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
