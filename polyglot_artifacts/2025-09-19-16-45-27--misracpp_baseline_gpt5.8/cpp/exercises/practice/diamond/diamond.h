#pragma once

#include <string>
#include <vector>

namespace diamond {

// Build the diamond as a vector of lines, preserving trailing spaces.
// Accepts letters 'A'..'Z' or 'a'..'z' (case-insensitive).
// Throws std::invalid_argument if the input is not an ASCII letter.
std::vector<std::string> (rows)(char letter);

// Build the diamond as a single string joined with '\n' between rows.
// No trailing newline is added. Trailing spaces within each line are preserved.
std::string (str)(char letter);

}  // namespace diamond
