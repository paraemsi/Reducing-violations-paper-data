#pragma once
#include <string>
#include <vector>

namespace diamond {

/**
 * Build an ASCII diamond whose widest point is the given upper-case letter.
 *
 * If the supplied character is not between 'A' and 'Z', an empty string is
 * returned.
 */
std::string make(char letter);

/**
 * Return the diamond as individual rows.
 *
 * Each element of the returned vector contains one line of the diamond,
 * including all leading and trailing spaces but without a terminating
 * newline. An empty vector is returned for invalid input.
 */
std::vector<std::string> rows(char letter);

}  // namespace diamond
