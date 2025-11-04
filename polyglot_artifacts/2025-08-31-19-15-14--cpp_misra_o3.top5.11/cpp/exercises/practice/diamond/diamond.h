#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Generate a diamond made of uppercase letters.
 *
 * The returned vector contains one string per row.  The first and
 * last rows hold a single 'A'.  The supplied letter determines the
 * widest row.  All requirements listed in the kata description are
 * fulfilled.
 *
 * @param letter An uppercase letter in the range 'A' .. 'Z'.
 * @return std::vector<std::string> Rows of the diamond, or an empty
 *         vector if the input is outside the supported range.
 */
[[nodiscard]] auto make_diamond(char const letter) -> std::vector<std::string>;
/**
 * @brief Convenience wrapper expected by the test-suite.
 *
 * This function simply forwards to make_diamond().
 *
 * @param letter An uppercase letter in the range 'A' .. 'Z'.
 * @return std::vector<std::string> The generated diamond rows.
 */
[[nodiscard]] auto rows(char const letter) -> std::vector<std::string>;

}  // namespace diamond
