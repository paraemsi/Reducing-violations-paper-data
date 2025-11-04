#pragma once

#include <string>
#include <vector>

#ifndef DIAMOND_NODISCARD
#  if defined(__cplusplus) && __cplusplus >= 201703L
#    if defined(__has_cpp_attribute)
#      if __has_cpp_attribute(nodiscard) >= 201603
#        define DIAMOND_NODISCARD [[nodiscard]]
#      else
#        define DIAMOND_NODISCARD
#      endif
#    else
#      define DIAMOND_NODISCARD
#    endif
#  else
#    define DIAMOND_NODISCARD
#  endif
#endif

namespace diamond {

// Generate a diamond for the given letter.
// - Accepts 'A'..'Z' or 'a'..'z'.
// - Returns a square string (width == height) with lines separated by '\n'.
// - Lines have symmetric leading/trailing spaces preserved.
// - Throws std::invalid_argument for non-alphabetic input.
DIAMOND_NODISCARD std::vector<std::string> rows(char letter);
DIAMOND_NODISCARD std::string make(char letter);

}  // namespace diamond
