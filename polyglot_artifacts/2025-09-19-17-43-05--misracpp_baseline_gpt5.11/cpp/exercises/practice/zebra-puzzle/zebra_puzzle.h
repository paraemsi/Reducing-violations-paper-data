#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;  // Nationality who drinks water
    std::string ownsZebra;    // Nationality who owns the zebra
};

Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
