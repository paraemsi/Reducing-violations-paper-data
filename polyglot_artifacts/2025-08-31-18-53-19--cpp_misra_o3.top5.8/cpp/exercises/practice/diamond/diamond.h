#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Generate a diamond shape composed of capital letters.
 *
 * The returned vector contains one string per row. Each string
 * has identical width and height forming a square, respecting
 * all requirements listed in the kata description.
 *
 * @param letter An uppercase letter between 'A' and 'Z' inclusive.
 * @return std::vector<std::string>  The diamond, top-to-bottom.
 *
 * @throw std::invalid_argument if the supplied letter is outside
 *        the valid range.
 */
auto make(char letter) -> std::vector<std::string>;

/**
 * @brief Convenience wrapper expected by the unit-tests.
 *
 * Delegates directly to make(letter).
 */
auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
