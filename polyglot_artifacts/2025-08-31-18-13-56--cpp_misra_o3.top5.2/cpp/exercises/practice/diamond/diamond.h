#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Build a textual diamond for the supplied uppercase letter.
 *
 * The returned string contains newline-delimited rows that form
 * a diamond satisfying the requirements of the diamond kata.
 *
 * @param letter An uppercase letter in the range 'A' .. 'Z'.
 * @return std::string A multi-line string representing the diamond.
 * @throw std::invalid_argument if letter is outside the permitted range.
 */
auto buildDiamond(char letter) -> std::string;

/**
 * @brief Return the diamond as individual rows without trailing newline.
 *
 * This overload is required by the unit-tests; it yields the same
 * rows that buildDiamond() joins with '\n'.
 *
 * @param letter An uppercase letter in the range 'A' .. 'Z'.
 * @return std::vector<std::string> The diamond represented row-by-row.
 */
auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
