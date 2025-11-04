#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <string>

namespace zebra_puzzle {

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};
    
//  Solve the classic Zebra Puzzle.
//
//  Returns:
//      Solution.drinksWater  – nationality of the person that drinks water
//      Solution.ownsZebra    – nationality of the person that owns the zebra
//
//  The function is pure and does not perform any I/O.
Solution solve();
    
}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
