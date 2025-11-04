#pragma once

#include <string>
#include <vector>

namespace diamond {

using DiamondString = std::vector<std::string>;

// Returns the rows of the diamond for the given letter.
DiamondString rows(char letter);

DiamondString make_diamond(char letter);

}  // namespace diamond
