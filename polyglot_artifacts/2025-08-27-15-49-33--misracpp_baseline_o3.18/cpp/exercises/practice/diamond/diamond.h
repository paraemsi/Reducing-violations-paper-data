#pragma once

#include <string>
#include <vector>

namespace diamond {

// Build a diamond for the supplied uppercase letter.
// Throws std::invalid_argument if the letter is not between 'A' and 'Z'.
// The returned vector contains each row of the diamond, without trailing
// newline characters. Leading and trailing spaces are preserved so that
// every row has the same length.
std::vector<std::string> rows(char letter);
inline std::vector<std::string> make(char letter) { return rows(letter); }

}  // namespace diamond
