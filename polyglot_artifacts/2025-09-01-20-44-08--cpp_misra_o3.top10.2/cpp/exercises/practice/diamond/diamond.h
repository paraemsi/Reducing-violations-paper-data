#pragma once

#include <string>
#include <vector>

/* Provide a portable replacement for [[nodiscard]] so the code compiles
 * with compilers that do not yet support the attribute (e.g. C++14). */
#if defined(__has_cpp_attribute)
#  if (__has_cpp_attribute(nodiscard) >= 201603L)
#    define DIAMOND_NODISCARD [[nodiscard]]
#  else
#    define DIAMOND_NODISCARD
#  endif
#else
#  define DIAMOND_NODISCARD
#endif

namespace diamond
{

// Create the diamond as a vector of rows.
// Each row is a std::string containing trailing spaces as required.
DIAMOND_NODISCARD auto make(char letter) -> std::vector<std::string>;

/* Alias required by the unit-tests.
 * rows() performs the same operation as make(). */
DIAMOND_NODISCARD auto rows(char letter) -> std::vector<std::string>;

// Convenience helper: return the whole diamond joined with '\n'.
DIAMOND_NODISCARD auto to_string(char letter) -> std::string;

}  // namespace diamond
