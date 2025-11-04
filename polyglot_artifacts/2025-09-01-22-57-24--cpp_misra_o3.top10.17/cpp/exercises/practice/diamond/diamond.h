#pragma once

#include <string>
#include <vector>

namespace diamond {

// Generate a textual diamond centred on the supplied upper-case letter.
// Returns each row of the diamond as a separate string without trailing new-line.
// Throws std::invalid_argument if letter is outside 'A'..'Z'.
auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
