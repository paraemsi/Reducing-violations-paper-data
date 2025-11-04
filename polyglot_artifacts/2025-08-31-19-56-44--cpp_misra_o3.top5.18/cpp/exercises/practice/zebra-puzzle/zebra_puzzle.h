#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

/**
 * @brief Solve the classic Zebra Puzzle.
 *
 * @return Solution  The nationalities of the residents who drink water and own the zebra.
 */
Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
