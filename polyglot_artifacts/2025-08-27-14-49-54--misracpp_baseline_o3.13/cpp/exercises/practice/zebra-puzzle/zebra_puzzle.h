#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

// Return the unique solution of the classic Zebra puzzle.
Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
