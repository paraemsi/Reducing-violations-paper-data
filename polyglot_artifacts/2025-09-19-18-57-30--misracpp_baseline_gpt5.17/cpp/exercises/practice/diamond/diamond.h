#pragma once
#include <string>
#include <vector>

 // Attribute portability helper for nodiscard
#if defined(__has_cpp_attribute)
#  if __has_cpp_attribute(nodiscard) >= 201603
#    define DIAMOND_NODISCARD [[nodiscard]]
#  endif
#endif

#ifndef DIAMOND_NODISCARD
#  if defined(__GNUC__) || defined(__clang__)
#    define DIAMOND_NODISCARD __attribute__((warn_unused_result))
#  else
#    define DIAMOND_NODISCARD
#  endif
#endif

namespace diamond {

// Returns the diamond as a vector of strings including trailing spaces.
// If the input is not an ASCII letter, returns an empty vector.
std::vector<std::string> rows(char letter);

}  // namespace diamond
