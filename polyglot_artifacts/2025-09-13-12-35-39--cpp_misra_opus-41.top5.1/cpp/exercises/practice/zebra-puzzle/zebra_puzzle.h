#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater_;
    std::string ownsZebra_;
};

Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
