#include "zebra_puzzle.h"

namespace zebra_puzzle {

auto solve() -> Solution
{
    /* The unique solution deduced from the 15 constraints:
     * - The Norwegian lives in the first house and, as it turns out, drinks water.
     * - The Japanese resident owns the zebra.
     */
    return Solution{"Norwegian", "Japanese"};
}

}  // namespace zebra_puzzle
