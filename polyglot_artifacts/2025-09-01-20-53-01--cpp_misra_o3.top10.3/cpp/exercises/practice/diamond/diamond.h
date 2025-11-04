#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * @brief Build a textual diamond whose widest row contains the given
 *        upper-case letter.
 *
 * Each element of the returned vector represents one row; no newline
 * characters are embedded.
 *
 * An empty vector is returned if the supplied letter is not an
 * upper-case ASCII letter present in the English alphabet.
 */
auto build(char letter) -> std::vector<std::string>;
auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
