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
 * @return Solution – with the name of the resident that drinks water and
 *                   the name of the resident that owns the zebra.
 */
Solution solve();
}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
