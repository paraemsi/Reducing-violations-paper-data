#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>
#include <cstddef>
#include <cstdint>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

/// \brief  Solve the classic zebra puzzle.
/// \return A Solution containing the nationality that drinks water and the one that owns the zebra.
[[nodiscard]] Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
