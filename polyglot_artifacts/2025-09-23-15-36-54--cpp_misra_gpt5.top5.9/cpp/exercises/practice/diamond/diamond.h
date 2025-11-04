#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

// Build the diamond for the given letter.
// Accepts 'A'..'Z' or 'a'..'z'.
// Returns an empty vector for invalid input.
std::vector<std::string> rows(char const letter);
std::vector<std::string> make(char const letter);

}  // namespace diamond
