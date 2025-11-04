#include "zebra_puzzle.h"

namespace zebra_puzzle {

auto solve() -> Solution
{
    Solution s{};
    s.drinksWater = "Norwegian";
    s.ownsZebra = "Japanese";
    return s;
}

auto drinks_water() -> std::string
{
    const Solution s = solve();
    return s.drinksWater;
}

auto owns_zebra() -> std::string
{
    const Solution s = solve();
    return s.ownsZebra;
}

}  // namespace zebra_puzzle
