#pragma once

#include <string>
#include <vector>

namespace diamond {

// Build a diamond string for the given letter (case-insensitive).
// - The returned string has height and width equal to (2*n - 1),
//   where n = toupper(letter) - 'A' + 1.
// - Each line retains trailing spaces to preserve the square shape.
// - Throws std::invalid_argument if letter is not in [A-Z]/[a-z].
std::vector<std::string> rows(char letter);
std::string make_diamond(char letter);

}  // namespace diamond
