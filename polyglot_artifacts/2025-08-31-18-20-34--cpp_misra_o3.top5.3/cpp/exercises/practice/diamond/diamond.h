#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Build the textual representation of a diamond.
 *
 * The returned vector contains every row, including the leading and trailing
 * space characters that keep the figure square.  If the supplied letter is not
 * found in the English alphabet the function returns an empty vector.
 *
 * @param letter Upper-case ASCII letter between 'A' and 'Z'.
 * @return Vector of rows that, when printed line by line, form the diamond.
 */
auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
