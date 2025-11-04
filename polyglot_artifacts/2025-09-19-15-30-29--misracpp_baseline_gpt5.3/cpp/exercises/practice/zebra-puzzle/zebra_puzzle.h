#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

// Solve the Zebra Puzzle and return the residents who drink water and own the zebra.
Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
