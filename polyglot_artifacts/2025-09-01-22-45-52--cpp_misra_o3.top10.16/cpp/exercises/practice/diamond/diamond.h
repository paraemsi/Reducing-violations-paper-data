#pragma once

#include <string>
#include <vector>
#include <cstddef>

namespace diamond {

/**
 * @brief Generate a diamond shape made of capital letters.
 *
 * The returned vector contains one string per line. Each line is already
 * padded with the required leading and trailing spaces so that all strings
 * have equal length, thereby producing a square output when printed.
 *
 * This function follows the behaviour described in the diamond kata:
 *   - The first and last lines contain only the letter 'A'.
 *   - The widest line contains the requested letter.
 *   - The diamond is horizontally and vertically symmetric.
 *
 * @param target A capital letter between 'A' and 'Z' (inclusive).
 * @return std::vector<std::string> The completed diamond, line-by-line.
 *
 * @throws std::invalid_argument if the supplied letter is not in the range.
 */
[[nodiscard]] auto make_diamond(char target) -> std::vector<std::string>;

/**
 * @brief Convenience wrapper expected by unit-tests.
 *
 * Simply forwards to make_diamond().
 */
[[nodiscard]] auto rows(char target) -> std::vector<std::string>;

}  // namespace diamond
