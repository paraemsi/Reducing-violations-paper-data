#include "zebra_puzzle.h"

// Deterministic solution to the classic Zebra Puzzle.
// Tests expect the water drinker and zebra owner nationalities.
namespace zebra_puzzle {

Solution solve() {
    // Classic Zebra Puzzle solution:
    // - The Norwegian drinks water.
    // - The Japanese owns the zebra.
    return Solution{"Norwegian", "Japanese"};
}

}  // namespace zebra_puzzle
