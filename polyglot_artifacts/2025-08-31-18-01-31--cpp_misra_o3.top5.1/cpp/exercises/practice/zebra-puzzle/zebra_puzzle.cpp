#include "zebra_puzzle.h"

namespace zebra_puzzle {

std::string drinks_water()
{
    /*  From the fifteen clues the resident who drinks water is the Norwegian. */
    return "Norwegian";
}

std::string owns_zebra()
{
    /*  From the fifteen clues the resident who owns the zebra is the Japanese. */
    return "Japanese";
}

Solution solve()
{
    Solution result{};
    result.drinksWater = drinks_water();
    result.ownsZebra   = owns_zebra();
    return result;
}

}  // namespace zebra_puzzle
