#pragma once

#include <string>
#include <vector>

#ifndef __has_cpp_attribute
#define __has_cpp_attribute(x) 0
#endif

#if __has_cpp_attribute(nodiscard)
#define DIAMOND_NODISCARD [[nodiscard]]
#else
#define DIAMOND_NODISCARD
#endif

namespace diamond {

 // Generate the diamond as a vector of lines (each line has equal width).
// Accepts uppercase or lowercase letters from 'A' to 'Z'.
// Throws std::invalid_argument if the input is not an alphabetic character A-Z.
DIAMOND_NODISCARD std::vector<std::string> rows(char letter);
DIAMOND_NODISCARD std::vector<std::string> make(char letter);

// Generate the diamond as a single string with newline separators.
// The returned string does not end with a trailing newline.
DIAMOND_NODISCARD std::string make_string(char letter);

}  // namespace diamond
