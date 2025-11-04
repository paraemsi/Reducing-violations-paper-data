#ifndef ZEBRA_PUZZLE_H
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

/**
 * Find the unique solution to the zebra puzzle.
 *
 * @return A Solution struct containing the nationality of
 *         the person who drinks water and the one who owns the zebra.
 */
Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
