#pragma once
#include <string>
#include <vector>

namespace diamond {

// Build a diamond of letters from 'A' to the given letter (case-insensitive).
// Returns a vector of strings, each string representing one row including
// leading and trailing spaces to maintain a square shape. Throws
// std::invalid_argument if letter is not in the range A-Z or a-z.
std::vector<std::string> rows(char letter);

}  // namespace diamond
