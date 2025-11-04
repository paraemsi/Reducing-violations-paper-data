#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

#include <array>
#include <cstdint>
#include <vector>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

/**
 * Solve the zebra puzzle and return the solution.
 * Provided for compatibility with test code expecting lowercase 'solve'.
 */
Solution solve();

Solution Solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
