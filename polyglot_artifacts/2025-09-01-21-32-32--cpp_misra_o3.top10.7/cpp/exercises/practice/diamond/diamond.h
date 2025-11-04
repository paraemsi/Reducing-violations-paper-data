#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>

namespace diamond {

/**
 * @brief Create a textual diamond for the supplied letter.
 *
 * The function returns a vector of equal-length strings.  Each string
 * represents one line of the diamond (without trailing new-line
 * characters).  The implementation follows the requirements of the
 * classic “diamond kata”.
 *
 * @param letter The widest letter of the diamond, expected to be an
 *               uppercase character present in the English alphabet.
 * @return std::vector<std::string> Diamond lines; an empty vector if
 *         the input character is not found in the alphabet.
 */
[[nodiscard]] auto make_diamond(char letter) -> std::vector<std::string>;

/**
 * @brief Convenience wrapper expected by the test-suite.
 *
 * The original code exposes make_diamond(), whereas the provided
 * tests look for rows().  The wrapper simply forwards the request to
 * make_diamond() to keep a single implementation.
 *
 * @param letter The widest letter of the diamond.
 * @return std::vector<std::string> Same contract as make_diamond().
 */
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
