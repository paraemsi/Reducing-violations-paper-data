#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater{};
    std::string ownsZebra{};
};

/*
 * Return the unique solution to the Zebra Puzzle.
 * According to the canonical reasoning, the Norwegian drinks water
 * and the Japanese person owns the zebra.
 */
[[nodiscard]] auto solve() -> Solution;

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
