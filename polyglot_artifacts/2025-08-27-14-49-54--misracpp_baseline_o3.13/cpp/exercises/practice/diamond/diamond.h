#pragma once

#include <string>
#include <vector>

namespace diamond {

// Return each row of the diamond as a separate string, preserving
// leading and trailing spaces so every row has the same width.
std::vector<std::string> rows(char letter);

// Return the complete diamond as a single string with '\n' separating rows
// (no trailing newline after the final row).
std::string make(char letter);

}  // namespace diamond
