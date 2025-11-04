#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <cstdint>
#include <string>

namespace zebra_puzzle {

enum class Nationality : std::uint8_t {
    Englishman,
    Spaniard,
    Ukrainian,
    Norwegian,
    Japanese
};

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

/**
 * @brief Solve the Zebra puzzle.
 *
 * @return Solution  The names of the residents who drink water and own the zebra.
 */
Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
