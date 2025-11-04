#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * Build a diamond whose widest row contains the supplied letter.
 *
 * Each element in the returned vector represents a single row of the
 * diamond (without a terminating newline).  The width of every row
 * equals rows(letter).size(), so the diamond is always square.
 *
 * If the supplied character is not an alphabetic letter in the range
 * 'A'-'Z' (case–insensitive) an std::invalid_argument is thrown.
 */
std::vector<std::string> rows(char letter);

}  // namespace diamond
