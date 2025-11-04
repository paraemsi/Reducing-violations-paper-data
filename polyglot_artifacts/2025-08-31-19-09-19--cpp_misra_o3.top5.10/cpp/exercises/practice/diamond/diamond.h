#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

/**
 * \brief Generate a textual diamond.
 *
 * The function returns a vector of strings, each string representing one
 * line of the diamond (without any trailing newline characters).
 *
 * \param letter The widest letter of the diamond ('A'-'Z').
 * \return Vector of lines forming the diamond.
 *
 * \throws std::invalid_argument if \p letter is outside the range 'A'-'Z'.
 */
[[nodiscard]] std::vector<std::string> make(char letter);
[[nodiscard]] std::vector<std::string> rows(char letter);

}  // namespace diamond
