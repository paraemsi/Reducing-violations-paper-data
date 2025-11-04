#pragma once
#include <string>
#include <vector>

namespace diamond {

// Generate a diamond string for the supplied uppercase letter (A-Z).
// Throws std::invalid_argument if the input is outside the range.
std::string generate(char letter);

// Return the diamond as a vector of rows (each row keeps its leading & trailing spaces).
// Throws std::invalid_argument if the input is outside the range.
std::vector<std::string> rows(char letter);

}  // namespace diamond
