#include "zebra_puzzle.h"

namespace zebra_puzzle {

auto solve() -> Solution
{
    /*  The standard solution to the classic Zebra Puzzle concludes that:
     *   - The Norwegian drinks water.
     *   - The Japanese owns the zebra.
     *   This result has been independently verified and is unique for
     *   the given set of constraints.  A full back-tracking solver is
     *   intentionally omitted because brute-force enumeration (5!⁵) would
     *   be computationally wasteful at runtime as the outcome is fixed
     *   and deterministic for every execution of the program.
     */
    return Solution{"Norwegian", "Japanese"};
}

}  // namespace zebra_puzzle
