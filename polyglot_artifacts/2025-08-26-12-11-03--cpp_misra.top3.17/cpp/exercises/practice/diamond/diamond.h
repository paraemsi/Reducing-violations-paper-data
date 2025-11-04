#pragma once

#include <string>
#include <vector>

namespace diamond {

using DiamondString = std::vector<std::string>;

// Alias for compatibility with test expectations
inline DiamondString rows(char letter) { return make_diamond(letter); }

DiamondString make_diamond(char letter);

}  // namespace diamond
