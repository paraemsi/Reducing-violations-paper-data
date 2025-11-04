#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

/// \brief Solve the Zebra Puzzle.
///
/// \return A Solution object containing:
///   - drinksWater : name of the resident who drinks water
///   - ownsZebra   : name of the resident who owns the zebra
///
Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
