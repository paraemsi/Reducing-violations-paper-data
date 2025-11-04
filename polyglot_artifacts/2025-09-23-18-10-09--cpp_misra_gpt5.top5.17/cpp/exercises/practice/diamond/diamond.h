#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

/* Build a diamond string for the given letter.
 * Returns an empty string if the letter is not an ASCII alphabet letter.
 */
std::string make_diamond(const char letter);

// Return the diamond as a vector of rows (each row is one string).
std::vector<std::string> rows(const char letter);

}  // namespace diamond
