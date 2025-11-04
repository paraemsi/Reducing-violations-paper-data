#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Create a diamond string for the supplied upper-case letter.
 *
 * The caller must provide a character in the range 'A' … 'Z'.
 * Behaviour is undefined for any other input.
 *
 * @param letter The widest letter in the diamond (must be upper-case).
 * @return std::string The rendered diamond without a trailing newline.
 */
[[nodiscard]] auto make_diamond(char letter) -> std::string;

/**
 * @brief Return the diamond as a vector of rows.
 *
 * Each element is a single row without newline termination.
 */
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
