#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Build a textual diamond for the supplied letter.
 *
 * The returned vector contains one string per row.
 *
 * @param letter An uppercase alphabetic character between 'A' and 'Z'.
 * @return std::vector<std::string> Diamond representation.
 */
auto build(char letter) -> std::vector<std::string>;

/**
 * @brief Convenience wrapper expected by the unit-tests.
 *
 * This simply forwards to build(letter).
 */
auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
