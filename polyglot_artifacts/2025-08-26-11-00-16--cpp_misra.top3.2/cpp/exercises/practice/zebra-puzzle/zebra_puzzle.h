#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>
#include <array>
#include <vector>
#include <cstdint>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater {};
    std::string ownsZebra {};
};

/**
 * Solve the zebra puzzle and return the solution.
 * (Tests expect the function to be named solve, not Solve.)
 */
Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
