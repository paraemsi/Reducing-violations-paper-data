#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>
#include <cstdint>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

/* Solve the Zebra Puzzle and return the two requested facts.
 * - drinksWater : nationality of the resident who drinks water
 * - ownsZebra   : nationality of the resident who owns the zebra
 */
[[nodiscard]] Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
