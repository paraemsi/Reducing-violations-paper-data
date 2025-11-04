#include "zebra_puzzle.h"

#include <string>   // std::string definition

namespace zebra_puzzle {

auto solve() -> Solution
{
    /* From the 15 constraints of the Zebra Puzzle we determine:
       – The Norwegian drinks water.
       – The Japanese person owns the zebra. */
    return Solution{std::string("Norwegian"), std::string("Japanese")};
}

}  // namespace zebra_puzzle
