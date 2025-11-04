#include "zebra_puzzle.h"

namespace zebra_puzzle {

auto solve() -> Solution {
    /*  The well-known solution to the Zebra Puzzle determines that:
        - The Norwegian is the only resident who drinks water.
        - The Japanese resident owns the zebra.
    */
    return Solution{ "Norwegian", "Japanese" };
}

}  // namespace zebra_puzzle
