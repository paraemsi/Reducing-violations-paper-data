#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

/**
 * @brief Simple aggregate containing the answers to the Zebra Puzzle.
 */
struct Solution {
    std::string drinksWater;  ///< Resident who drinks water
    std::string ownsZebra;    ///< Resident who owns the zebra
};

/**
 * @brief Solve the Zebra Puzzle and obtain both answers at once.
 *
 * @return Solution with the water-drinker and zebra-owner filled-in.
 */
Solution solve();

/**
 * @brief Get the nationality of the resident who drinks water.
 *
 * @return The resident that drinks water.
 */
std::string drinks_water();

/**
 * @brief Get the nationality of the resident who owns the zebra.
 *
 * @return The resident that owns the zebra.
 */
std::string owns_zebra();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
