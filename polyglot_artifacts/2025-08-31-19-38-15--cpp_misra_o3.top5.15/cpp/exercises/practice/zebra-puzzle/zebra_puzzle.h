#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    /* Nationality of the resident who drinks water */
    std::string drinksWater;
    /* Nationality of the resident who owns the zebra */
    std::string ownsZebra;
};

auto solve() -> Solution;

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
