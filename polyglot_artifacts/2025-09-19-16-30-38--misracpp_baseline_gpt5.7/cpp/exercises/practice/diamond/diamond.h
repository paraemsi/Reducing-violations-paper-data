#pragma once

#include <string>
#include <vector>

#if defined(__has_cpp_attribute)
#  if __cplusplus >= 201703L && __has_cpp_attribute(nodiscard)
#    define DIAMOND_NODISCARD [[nodiscard]]
#  else
#    define DIAMOND_NODISCARD
#  endif
#else
#  if __cplusplus >= 201703L
#    define DIAMOND_NODISCARD [[nodiscard]]
#  else
#    define DIAMOND_NODISCARD
#  endif
#endif

namespace diamond {

// Build a diamond string for the given letter.
// - Accepts ASCII letters; lower-case is converted to upper-case.
// - Throws std::invalid_argument if the letter is not between 'A' and 'Z'.
 // - Returns a string consisting of lines joined by '\n', with each line
//   padded with spaces to make the diamond a square (width == height).
DIAMOND_NODISCARD std::vector<std::string> rows(char letter);
DIAMOND_NODISCARD std::string make_diamond(char letter);

}  // namespace diamond
