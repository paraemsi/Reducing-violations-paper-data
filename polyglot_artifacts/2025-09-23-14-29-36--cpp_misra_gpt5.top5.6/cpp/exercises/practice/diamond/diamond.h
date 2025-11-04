#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

// Build a diamond shape for the given letter.
// - Accepts either uppercase or lowercase English letters (A-Z or a-z).
// - Returns the diamond as a vector of lines, each line preserving leading and trailing spaces.
// - Returns an empty vector if the input is not an English alphabet letter.
std::vector<std::string> make_diamond(char letter);
std::vector<std::string> rows(char letter);

}  // namespace diamond
