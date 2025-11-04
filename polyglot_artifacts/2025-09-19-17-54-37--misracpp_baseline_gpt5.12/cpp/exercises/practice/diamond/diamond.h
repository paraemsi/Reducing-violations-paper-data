#pragma once

#include <string>
#include <stdexcept>
#include <vector>

#if defined(__has_cpp_attribute)
#  if __has_cpp_attribute(nodiscard) && __cplusplus >= 201703L
#    define DIAMOND_NODISCARD [[nodiscard]]
#  else
#    define DIAMOND_NODISCARD
#  endif
#else
#  define DIAMOND_NODISCARD
#endif

namespace diamond {

// Builds a diamond string using uppercase letters from 'A' up to `letter`.
// The result has width == height, includes trailing spaces to keep lines equal
// length, and contains no trailing newline at the end of the string.
// Throws std::invalid_argument if `letter` is not an alphabetic character A-Z or a-z.
DIAMOND_NODISCARD std::vector<std::string> rows(char letter);
DIAMOND_NODISCARD std::string make_diamond(char letter);

}  // namespace diamond
