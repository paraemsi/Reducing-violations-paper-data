#pragma once

#include <string>
#include <vector>

#if defined(__has_cpp_attribute)
#  if __has_cpp_attribute(nodiscard) && (__cplusplus >= 201703L)
#    define DIAMOND_NODISCARD [[nodiscard]]
#  else
#    define DIAMOND_NODISCARD
#  endif
#else
#  define DIAMOND_NODISCARD
#endif


namespace diamond {

/**
 * Generate the textual representation of a diamond whose widest point
 * corresponds to the supplied uppercase letter.
 *
 * The returned std::string contains newline-separated lines and does not
 * finish with a trailing newline.
 *
 * @param letter An uppercase character from 'A' to 'Z'.
 * @return The diamond as a std::string.
 * @throws std::invalid_argument if the letter is outside the range ['A', 'Z'].
 */
DIAMOND_NODISCARD auto generate(char letter) -> std::string;
DIAMOND_NODISCARD auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
