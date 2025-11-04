#pragma once

#include <string>
#include <vector>

namespace diamond {

using DiamondString = std::vector<std::string>;

// Alias for test compatibility
inline DiamondString rows(char letter) { return make_diamond(letter); }

DiamondString make_diamond(char letter);

}  // namespace diamond
