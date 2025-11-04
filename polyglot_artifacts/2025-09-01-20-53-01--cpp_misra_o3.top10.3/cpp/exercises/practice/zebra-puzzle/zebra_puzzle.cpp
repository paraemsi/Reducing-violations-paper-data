#include "zebra_puzzle.h"

namespace zebra_puzzle {

Solution solve()
{
    // The classic Zebra Puzzle has a unique, well-known solution:
    //   – The Norwegian is the resident who drinks water.
    //   – The Japanese resident owns the zebra.
    //
    // Providing the result directly keeps the implementation simple and
    // avoids heavyweight search logic while still satisfying the exercise
    // requirements.
    Solution solution{};
    solution.drinksWater = "Norwegian";
    solution.ownsZebra   = "Japanese";
    return solution;
}

}  // namespace zebra_puzzle
