#pragma once

#include <string>
#include <vector>

namespace diamond {

// Generate a diamond pattern with the given letter at the widest point
// Parameter: letter - the widest letter in the diamond (must be 'A' to 'Z')
// Returns: vector of strings, one for each row of the diamond
std::vector<std::string> rows(char letter);

}  // namespace diamond
