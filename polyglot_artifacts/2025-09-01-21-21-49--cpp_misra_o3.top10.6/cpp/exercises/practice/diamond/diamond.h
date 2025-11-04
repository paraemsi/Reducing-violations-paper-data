#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Create a diamond representation for the supplied uppercase letter.
 *
 * @param letter An uppercase character in the range 'A'..'Z'.
 * @return std::string A square, horizontally and vertically symmetric diamond.
 * @throws std::invalid_argument if letter is outside 'A'..'Z'.
 */
[[nodiscard]] auto create_diamond(char letter) -> std::string;
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
