#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

// Build a diamond of uppercase letters from 'A' to the supplied letter.
// Returns a vector of rows (each row is width characters wide, including spaces).
// If the supplied letter is not an English alphabet letter, returns an empty vector.
std::vector<std::string> make(char letter);
std::vector<std::string> rows(char letter);

}  // namespace diamond
