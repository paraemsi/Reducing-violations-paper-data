#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

/**
 * \brief Solve the Zebra Puzzle.
 *
 * \return Solution struct containing:
 *         - drinksWater : the nationality of the resident who drinks water
 *         - ownsZebra   : the nationality of the resident who owns the zebra
 */
auto solve() -> Solution;

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
