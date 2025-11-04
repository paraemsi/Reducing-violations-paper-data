#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Build the diamond as a vector of strings, one entry per row.
 *
 * @param letter The widest letter of the requested diamond. Must be an
 *               uppercase alphabetic character in the range ['A', 'Z'].
 * @return std::vector<std::string> The diamond, top-to-bottom.
 */
auto make_diamond(char letter) -> std::vector<std::string>;

/**
 * @brief Compatibility wrapper expected by the test-suite.
 *
 * Simply forwards to make_diamond(letter).  Kept in the header so no
 * additional translation-unit is required.
 */
inline auto rows(char letter) -> std::vector<std::string>
{
    return make_diamond(letter);
}

/**
 * @brief Convenience wrapper that joins the rows of the diamond with '\n'.
 *
 * The returned string does NOT finish with a trailing newline, matching
 * the examples in the kata description.
 *
 * @param letter The widest letter of the requested diamond.
 * @return std::string The complete diamond as a single string.
 */
auto to_string(char letter) -> std::string;

}  // namespace diamond
