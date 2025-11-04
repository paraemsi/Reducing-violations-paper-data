#pragma once
#include <string>
#include <vector>

#if defined(__has_cpp_attribute)
#  if (__cplusplus >= 201703L) && __has_cpp_attribute(nodiscard)
#    define DIAMOND_NODISCARD [[nodiscard]]
#  else
#    define DIAMOND_NODISCARD
#  endif
#else
#  if (__cplusplus >= 201703L)
#    define DIAMOND_NODISCARD [[nodiscard]]
#  else
#    define DIAMOND_NODISCARD
#  endif
#endif

namespace diamond {

// Generate a diamond shape up to the given letter.
// Accepts either uppercase or lowercase ASCII letters.
// Returns an empty string for invalid input.
DIAMOND_NODISCARD std::vector<std::string> rows(char letter);
DIAMOND_NODISCARD std::string make(char letter);

}  // namespace diamond
