#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

// Returns the diamond as lines with spaces preserved (including trailing spaces).
// Input must be an uppercase letter 'A'..'Z'; otherwise std::invalid_argument is thrown.
using Lines = std::vector<std::string>;
Lines make(char const letter);

Lines rows(char const letter);

}  // namespace diamond
