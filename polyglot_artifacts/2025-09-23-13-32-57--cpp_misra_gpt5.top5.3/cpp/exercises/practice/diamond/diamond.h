#pragma once

#include <string>
#include <vector>

namespace diamond {

 // Build a diamond string for the specified alphabetic letter.
 // Returns an empty string if letter is not an English alphabet character.
 std::vector<std::string> rows(char letter);  // NOLINT
 std::string make_diamond(char letter);       // NOLINT

}  // namespace diamond
