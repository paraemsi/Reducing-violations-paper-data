#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Build a textual diamond up to the supplied letter.
 *
 * The function returns each row (including trailing spaces) as an
 * element of the returned vector.  An invalid argument is reported
 * through an exception.
 *
 * @param up_to  An uppercase letter in the range 'A'–'Z'.
 * @return std::vector<std::string>  The diamond, one string per row.
 *
 * @throws std::invalid_argument  If the supplied character is not
 *                                an uppercase letter in the valid range.
 */
[[nodiscard]] auto make(char up_to) -> std::vector<std::string>;

[[nodiscard]] auto rows(char up_to) -> std::vector<std::string>;

}  // namespace diamond
