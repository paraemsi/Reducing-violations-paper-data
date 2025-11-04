#pragma once

#include <string>
#include <vector>

namespace diamond {

// Build a diamond string for the given uppercase letter.
// The resulting string contains width == height lines separated by '\n'.
//// Each line preserves trailing spaces to satisfy symmetry requirements.
std::vector<std::string> rows(const char letter);
std::string make_diamond(const char letter);

}  // namespace diamond
