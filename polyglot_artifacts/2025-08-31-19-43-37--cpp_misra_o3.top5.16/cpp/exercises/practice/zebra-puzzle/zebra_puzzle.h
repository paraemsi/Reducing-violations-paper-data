#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>  // NOLINT(misra-cpp) -- std::string required to convey textual results

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater{};
    std::string ownsZebra{};
};

auto solve() -> Solution;

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
