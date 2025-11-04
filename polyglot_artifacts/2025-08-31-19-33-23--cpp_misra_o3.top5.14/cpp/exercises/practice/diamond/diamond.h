#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Build a textual diamond from the given uppercase letter.
 *
 * The function generates the classic “diamond kata” representation
 * where the supplied letter is the widest row and both the width
 * and the height of the resulting figure are identical.
 *
 * @param letter An uppercase alphabetic character in the range 'A'–'Z'.
 * @return std::string The fully-formed diamond, lines separated by '\n'.
 * @throws std::invalid_argument If @p letter is outside the allowed range.
 */
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>;
[[nodiscard]] auto build(char letter) -> std::string;

}  // namespace diamond
