#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * \brief Create the textual representation of a diamond for a given letter.
 *
 * The returned vector contains one entry per line; no newline characters are
 * embedded.  Behaviour is undefined for characters outside the range
 * 'A'..'Z'.
 *
 * \param letter The widest letter of the diamond (must be 'A'-'Z').
 * \return Vector of lines forming a square, symmetric diamond.
 */
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>;
[[nodiscard]] inline auto make(char letter) -> std::vector<std::string> {
    return rows(letter);
}

}  // namespace diamond
