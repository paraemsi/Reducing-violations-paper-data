#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

/* Holds the final answer of the zebra puzzle. */
struct Solution {
    std::string drinksWater; /* Resident who drinks water */
    std::string ownsZebra;   /* Resident who owns the zebra */
};

Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
