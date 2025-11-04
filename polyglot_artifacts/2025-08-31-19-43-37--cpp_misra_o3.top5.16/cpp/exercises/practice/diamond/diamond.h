#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Build an alphabetical diamond.
 *
 * The function returns a square, horizontally and vertically symmetric
 * diamond composed of capital letters starting with 'A' at the top and
 * bottom and using the supplied letter at its widest point.
 *
 * Example for input 'C':
 *   "··A··\n"
 *   "·B·B·\n"
 *   "C···C\n"
 *   "·B·B·\n"
 *   "··A··"
 *
 * Spaces are regular space characters (0x20).  The calling code may
 * replace them with another visible glyph for debugging if desired.
 *
 * @param letter  An upper-case Latin letter in the range 'A'–'Z'.
 * @return        The rendered diamond as a single string with '\n'
 *                line breaks.  No trailing '\n' after the last row.
 */
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>;
[[nodiscard]] auto make_diamond(char letter) -> std::string;

}  // namespace diamond
