#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater{};
    std::string ownsZebra{};
};

inline bool operator==(const Solution &lhs, const Solution &rhs) {
    return (lhs.drinksWater == rhs.drinksWater) && (lhs.ownsZebra == rhs.ownsZebra);
}

inline bool operator!=(const Solution &lhs, const Solution &rhs) {
    return !(lhs == rhs);
}

Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
