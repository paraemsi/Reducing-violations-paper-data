#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

/*
 * Returns the solution to the Zebra Puzzle.
 * The strings contain the nationalities of
 * the resident who drinks water and the resident who owns the zebra.
 */
Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
