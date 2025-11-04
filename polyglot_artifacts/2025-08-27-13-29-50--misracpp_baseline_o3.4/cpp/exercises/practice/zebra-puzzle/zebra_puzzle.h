#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;

    // Equality comparison helpers to simplify unit-testing.
    bool operator==(const Solution& other) const {
        return drinksWater == other.drinksWater && ownsZebra == other.ownsZebra;
    }
    bool operator!=(const Solution& other) const {
        return !(*this == other);
    }
};

Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
