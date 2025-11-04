#pragma once

#include <string>
#include <vector>
#include <cstddef>   // for std::size_t
#include <cstdint>   // for fixed-width integers

namespace diamond {

/**
 * \brief Generate a diamond for the supplied uppercase letter.
 *
 * The function builds each line of the diamond as a separate std::string.
 * No trailing newline characters are added; use to_string() if a single
 * newline-separated string is desired.
 *
 * \param letter  The uppercase letter that forms the widest point ('A'–'Z').
 * \return        The diamond as a sequence of lines.
 */
auto generate(char letter) -> std::vector<std::string>;

/**
 * \brief Compatibility wrapper expected by the unit-tests.
 *
 * rows() simply forwards to generate().
 */
auto rows(char letter) -> std::vector<std::string>;

/**
 * \brief Utility helper that converts the vector returned by generate() into
 *        a single string separated by '\n'.
 */
auto to_string(const std::vector<std::string>& lines) -> std::string;

}  // namespace diamond
