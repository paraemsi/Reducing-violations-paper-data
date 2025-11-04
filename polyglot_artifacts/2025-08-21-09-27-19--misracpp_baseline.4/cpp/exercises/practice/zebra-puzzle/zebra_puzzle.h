#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>
#include <vector>

namespace zebra_puzzle {

// Use camelCase to match test expectations
struct Solution {
    std::string drinksWater{};
    std::string ownsZebra{};
};

/**
 * Returns the solution to the zebra puzzle.
 * (Tests expect the function to be named solve, not Solve.)
 */
Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
