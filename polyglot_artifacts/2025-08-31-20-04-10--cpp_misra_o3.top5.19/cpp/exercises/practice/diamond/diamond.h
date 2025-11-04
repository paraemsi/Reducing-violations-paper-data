#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Build the diamond as a vector of rows.
 *
 * @param letter The widest letter (must be an upper-case alphabetic character).
 * @return Vector with each row of the diamond (no trailing '\n').
 */
auto make(char letter) -> std::vector<std::string>;

/**
 * @brief Alias kept for unit-test compatibility.
 *
 * @param letter The widest letter (must be an upper-case alphabetic character).
 * @return Vector with each row of the diamond.
 */
auto rows(char letter) -> std::vector<std::string>;

/**
 * @brief Convenience helper that returns the whole diamond as a single string
 *        (rows separated by '\n', final row *without* trailing newline).
 *
 * @param letter The widest letter (must be an upper-case alphabetic character).
 * @return Diamond rendered into a single std::string.
 */
auto make_string(char letter) -> std::string;

}  // namespace diamond
