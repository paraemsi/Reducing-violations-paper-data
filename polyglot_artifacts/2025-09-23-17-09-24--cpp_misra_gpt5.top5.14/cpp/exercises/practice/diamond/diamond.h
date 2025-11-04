#pragma once

#include <string>
#include <vector>

namespace diamond {

 // Build the diamond as a vector of strings, each string is one row.
 // Accepts alphabetic input (case-insensitive). Returns empty on invalid input.
auto rows(char letter) -> std::vector<std::string>;
auto make_diamond(char letter) -> std::vector<std::string>;

// Convenience: build the diamond as a single string with newline separators.
// Returns empty string on invalid input.
auto make_diamond_string(char letter) -> std::string;

}  // namespace diamond
