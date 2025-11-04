#pragma once

#include <string>
#include <vector>

#if (__cplusplus >= 201703L)
#define DIAMOND_NODISCARD [[nodiscard]]
#else
#define DIAMOND_NODISCARD
#endif

namespace diamond {

/**
 * @brief Generate a diamond representation for the supplied uppercase letter.
 *
 * Each element of the returned vector is one row of the diamond.  The caller
 * can join the rows with newline characters if a single string view is needed.
 *
 * @param letter  An uppercase alphabetic character between 'A' and 'Z'.
 * @return std::vector<std::string>  The rows that form the diamond.
 */
DIAMOND_NODISCARD std::vector<std::string> make_diamond(char letter);

/* Convenience wrapper kept for compatibility with the test-suite. */
DIAMOND_NODISCARD std::vector<std::string> rows(char letter);

}  // namespace diamond

#undef DIAMOND_NODISCARD
