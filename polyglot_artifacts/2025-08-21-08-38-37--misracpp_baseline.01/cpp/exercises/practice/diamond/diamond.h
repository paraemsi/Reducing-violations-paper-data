#pragma once

#include <string>
#include <vector>

namespace diamond {

// Returns a vector of strings representing the diamond for the given uppercase letter.
// Each string is a row of the diamond, with spaces as padding.
std::vector<std::string> rows(char letter);

}  // namespace diamond
