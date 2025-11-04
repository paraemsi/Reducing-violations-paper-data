#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * Build a textual diamond using capital letters from 'A' up to the supplied
 * letter.
 *
 * Examples:
 *   make('A') returns "A"
 *   make('C') returns
 *     "  A  \n"
 *     " B B \n"
 *     "C   C\n"
 *     " B B \n"
 *     "  A  "
 *
 * The function throws std::invalid_argument if the input is not between
 * 'A' and 'Z'.
 */
std::vector<std::string> rows(char letter);
std::string make(char letter);

}  // namespace diamond
