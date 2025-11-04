#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

// The struct fields must match the test names: drinksWater, ownsZebra
struct Solution {
    std::string drinksWater{};
    std::string ownsZebra{};
};

// Returns the solution to the Zebra Puzzle.
Solution Solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
