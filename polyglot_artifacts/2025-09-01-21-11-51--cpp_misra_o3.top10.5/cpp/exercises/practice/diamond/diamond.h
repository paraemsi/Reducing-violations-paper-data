#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Generate the textual representation of a diamond.
 *
 * The function follows the “diamond kata” specification: given an uppercase
 * letter between 'A' and 'Z' (inclusive) it returns a square, horizontally-
 * and vertically-symmetric diamond of letters with the supplied letter at
 * the widest point.
 *
 * An empty string is returned if the input letter is outside the supported
 * range.
 *
 * @param letter  Letter that defines the size of the diamond (must be 'A'–'Z')
 * @return std::string  Multiline string containing the diamond (no trailing
 *                      newline after the last row).
 */
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>;
[[nodiscard]] auto make(char letter) -> std::string;

}  // namespace diamond
