#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * Build a diamond of uppercase letters starting with 'A' and having `letter`
 * at its widest point.
 *
 * Example for letter == 'C':
 *   "  A  \n"
 *   " B B \n"
 *   "C   C\n"
 *   " B B \n"
 *   "  A  "
 *
 * The returned string contains '\n' line separators except on the last line.
 *
 * Throws std::invalid_argument if letter is not in the range ['A', 'Z'].
 */
/**
 * Return the diamond rows as a vector of strings without trailing newlines.
 *
 * Throws std::invalid_argument if letter is not in the range ['A', 'Z'].
 */
std::vector<std::string> rows(char letter);

/**
 * Return the diamond rows concatenated with '\n' separators.
 */
std::string make(char letter);

}  // namespace diamond
