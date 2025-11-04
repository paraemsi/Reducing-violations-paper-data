#pragma once

#include <string>
#include <vector>

namespace diamond {

/* Create a diamond string for the given uppercase letter (e.g., 'A'..'Z').
   Returns an empty string if the input letter is not found in the alphabet. */
std::vector<std::string> rows(char letter);
std::string make_diamond(char letter);

}  // namespace diamond
