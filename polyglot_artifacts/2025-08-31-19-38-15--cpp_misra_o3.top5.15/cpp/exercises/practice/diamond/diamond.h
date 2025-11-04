#pragma once

#include <cstdint>
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

/*
 * Generate the diamond as a collection of lines.
 * Each element of the returned vector is one row of the diamond
 * without a trailing line-feed.
 */
DIAMOND_NODISCARD auto generate(char letter) -> std::vector<std::string>;

/*
 * Public wrapper expected by the tests.
 * Simply forwards to generate() to keep a stable API.
 */
DIAMOND_NODISCARD auto rows(char letter) -> std::vector<std::string>;

/*
 * Convenience helper that joins the lines produced by generate()
 * with '\n' and returns the complete diamond in a single string.
 */
DIAMOND_NODISCARD auto generate_string(char letter) -> std::string;

}  // namespace diamond
