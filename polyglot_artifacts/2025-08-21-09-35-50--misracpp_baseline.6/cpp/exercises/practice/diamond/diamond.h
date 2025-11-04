#pragma once

#include <string>
#include <vector>

namespace diamond {

std::string make_diamond(char letter);

// Returns the diamond as a vector of strings, one per row.
std::vector<std::string> rows(char letter);

}  // namespace diamond
