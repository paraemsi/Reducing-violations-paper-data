#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>
#include <utility>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;

    Solution() = default;
    Solution(std::string drinks, std::string zebra)
        : drinksWater(std::move(drinks)), ownsZebra(std::move(zebra)) {}
};

Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
