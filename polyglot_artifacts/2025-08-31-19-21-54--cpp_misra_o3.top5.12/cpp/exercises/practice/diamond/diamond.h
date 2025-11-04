#pragma once

#include <string>
#include <vector>

#if defined(__has_cpp_attribute)
#if __has_cpp_attribute(nodiscard)
#define DIAMOND_NODISCARD [[nodiscard]]
#else
#define DIAMOND_NODISCARD
#endif
#else
#define DIAMOND_NODISCARD
#endif

namespace diamond {

/**
 * @brief Generate a diamond made of capital letters.
 *
 * The diamond fulfils the classic “diamond-kata” requirements:
 *  - Starts with ‘A’, ends with ‘A’.
 *  - Widest row contains the requested letter twice (once if that letter is ‘A’).
 *  - Horizontally and vertically symmetric, square shape.
 *
 * When the supplied character is not an upper-case letter in the ASCII
 * alphabet (A-Z) an empty vector is returned.
 *
 * NOTE: No arithmetic or relational operations are performed on characters,
 * complying with the given MISRA rule – all index manipulation is done on
 * integral types while characters are obtained only through indexing an
 * alphabet string.
 *
 * @param last Letter that forms the widest point.
 * @return std::vector<std::string> Diamond, each row as a string.
 */
DIAMOND_NODISCARD auto make(char last) -> std::vector<std::string>;
DIAMOND_NODISCARD auto rows(char last) -> std::vector<std::string>;

}  // namespace diamond
