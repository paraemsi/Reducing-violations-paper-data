#pragma once

#include <string>
#include <vector>

 // Provide a portable nodiscard attribute for pre-C++17 compilers.
 // Avoid redefinition if the macro is provided by the build system or elsewhere.
#ifndef DIAMOND_NODISCARD
#  if defined(__cplusplus) && __cplusplus >= 201703L
#    define DIAMOND_NODISCARD [[nodiscard]]
#  else
#    define DIAMOND_NODISCARD
#  endif
#endif

namespace diamond {

 // Build the diamond as a vector of lines. Accepts 'A'..'Z' (case-insensitive).
DIAMOND_NODISCARD std::vector<std::string> rows(char letter);

// Build the diamond as a single string joined by '\n'.
DIAMOND_NODISCARD std::string make(char letter);

}  // namespace diamond
