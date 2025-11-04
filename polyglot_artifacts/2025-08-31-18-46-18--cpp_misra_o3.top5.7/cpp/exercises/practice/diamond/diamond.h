#pragma once

#include <cstddef>      // for std::size_t
#include <cstdint>      // fixed-width integer types (MISRA requirement)
#include <string>       // for std::string
#include <string_view>  // for std::string_view
#include <vector>       // for std::vector

/* Ensure portability of the nodiscard attribute */
#ifndef DIAMOND_NODISCARD
#  if defined(__has_cpp_attribute)
#    if __has_cpp_attribute(nodiscard)
#      define DIAMOND_NODISCARD [[nodiscard]]
#    else
#      define DIAMOND_NODISCARD
#    endif
#  else
#    define DIAMOND_NODISCARD
#  endif
#endif

namespace diamond {

/**
 * \brief Build a diamond string for the supplied uppercase letter.
 *
 * The returned string contains newline ('\n') separated rows that satisfy
 * the requirements described in the kata statement.  An empty string is
 * returned if @p target is not an uppercase character in the range 'A'–'Z'.
 *
 * MISRA-C++ rules are observed:
 * - No arithmetic or relational operations on `char`; we only use equality.
 * - Fixed-width integer types and `std::size_t` are used for all numeric work.
 *
 * \param target   The widest letter of the diamond (must be 'A'..'Z').
 * \return         The formatted diamond or empty string on invalid input.
 */
DIAMOND_NODISCARD auto make(char target) -> std::string;

/**
 * \brief Return the diamond as a vector of rows.
 *
 * Convenience wrapper around make() used by tests.
 *
 * \param target   The widest letter of the diamond (must be 'A'..'Z').
 * \return         Each row as an element; empty if input invalid.
 */
DIAMOND_NODISCARD auto rows(char target) -> std::vector<std::string>;

}  // namespace diamond
