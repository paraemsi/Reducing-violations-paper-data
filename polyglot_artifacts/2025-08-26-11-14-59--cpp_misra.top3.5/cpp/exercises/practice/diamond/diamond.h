#pragma once

#include <string>
#include <vector>

namespace diamond {

using DiamondString = std::vector<std::string>;

// Alias for test compatibility: rows is the required function name
inline DiamondString rows(char letter) {
    return make_diamond(letter);
}

DiamondString make_diamond(char letter);

}  // namespace diamond
