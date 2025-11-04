#pragma once

#include <string>
#include <vector>

namespace diamond {

// Generate the diamond lines for the given input character.
// - Input is normalized to uppercase alphabetic; non-letters default to 'A'.
// - Returns a square diamond (width == height) as lines without trailing spaces trimmed.
std::vector<std::string> make_diamond(const char letter) noexcept;
std::vector<std::string> rows(const char letter) noexcept;

}  // namespace diamond
