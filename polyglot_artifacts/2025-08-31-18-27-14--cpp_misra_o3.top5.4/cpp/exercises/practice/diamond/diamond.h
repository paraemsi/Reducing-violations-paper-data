#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Generate a diamond string whose widest point is the supplied letter.
 *
 * The behaviour follows the rules described in the kata description.
 *
 * @param letter The uppercase letter ('A'‒'Z') defining the diamond size.
 * @return std::string The formatted diamond without a trailing newline.
 * @throws std::invalid_argument If letter is not between 'A' and 'Z'.
 */
auto rows(char letter) -> std::vector<std::string>;
auto make_diamond(char letter) -> std::string;

}  // namespace diamond
