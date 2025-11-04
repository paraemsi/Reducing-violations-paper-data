#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

/**
 * @brief Solve the Zebra Puzzle and return the nationalities that
 *        (a) drink water and (b) own the zebra.
 *
 * @return zebra_puzzle::Solution with the answers filled in.
 */
auto solve() -> Solution;

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
