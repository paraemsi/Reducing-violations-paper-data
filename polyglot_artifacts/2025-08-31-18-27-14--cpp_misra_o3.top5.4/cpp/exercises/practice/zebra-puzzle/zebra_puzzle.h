#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;  // nationality of the resident who drinks water
    std::string ownsZebra;    // nationality of the resident who owns the zebra
};

/**
 * \brief Solve the classic Zebra Puzzle.
 *
 * \return Solution structure containing:
 *         - drinksWater : the nationality of the resident who drinks water
 *         - ownsZebra   : the nationality of the resident who owns the zebra
 */
auto solve() -> Solution;

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
