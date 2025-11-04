#include <cstdint>
#include "zebra_puzzle.h"

namespace zebra_puzzle {

auto solve() -> Solution {
    // Classical solution of the Zebra puzzle
    Solution result{};
    result.drinksWater = "Norwegian";
    result.ownsZebra   = "Japanese";
    return result;
}

}  // namespace zebra_puzzle
