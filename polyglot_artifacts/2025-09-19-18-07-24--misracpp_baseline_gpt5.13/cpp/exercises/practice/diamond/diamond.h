#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * Returns the diamond as a vector of lines, each line includes trailing spaces.
 * Throws std::invalid_argument if letter is not alphabetic A-Z/a-z.
 */
std::vector<std::string> rows(char letter);

// Convenience: returns the diamond as a single string joined by '\n'.
std::string str(char letter);

}  // namespace diamond
