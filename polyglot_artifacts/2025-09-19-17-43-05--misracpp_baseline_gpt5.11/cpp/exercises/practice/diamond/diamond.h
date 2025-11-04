#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#if defined(__has_cpp_attribute)
#  if __has_cpp_attribute(nodiscard)
#    define DIAMOND_NODISCARD [[nodiscard]]
#  else
#    define DIAMOND_NODISCARD
#  endif
#else
#  define DIAMOND_NODISCARD
#endif

namespace diamond {

 // Returns the diamond as a vector of lines, each line padded with
 // leading and trailing spaces to ensure a square shape.
 // Throws std::invalid_argument if letter is not in A-Z (case-insensitive).
DIAMOND_NODISCARD std::vector<std::string> lines(char letter);

// Returns the diamond as a vector of lines; alias kept for test compatibility.
DIAMOND_NODISCARD std::vector<std::string> rows(char letter);

// Returns the diamond as a single string joined by '\n' without a trailing newline.
// Throws std::invalid_argument if letter is not in A-Z (case-insensitive).
DIAMOND_NODISCARD std::string make(char letter);

}  // namespace diamond
