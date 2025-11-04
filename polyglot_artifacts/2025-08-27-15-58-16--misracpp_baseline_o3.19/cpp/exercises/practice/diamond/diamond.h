#pragma once

#include <string>
#include <vector>

namespace diamond {

// Build and return a diamond ending with the supplied uppercase letter.
// Example: make_diamond('C') ->
//   "  A  \n"
//   " B B \n"
//   "C   C\n"
//   " B B \n"
//   "  A  "
std::string make_diamond(char letter);
std::vector<std::string> rows(char letter);

}  // namespace diamond
