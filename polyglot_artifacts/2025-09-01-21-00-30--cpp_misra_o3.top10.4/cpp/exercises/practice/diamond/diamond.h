#pragma once

#include <string>
#include <vector>

#ifndef DIAMOND_NODISCARD
 #if (__cplusplus >= 201703L)
  #define DIAMOND_NODISCARD [[nodiscard]]
 #else
  #define DIAMOND_NODISCARD
 #endif
#endif

namespace diamond {

/*
 * create_diamond
 *
 * Generate the diamond pattern for the supplied upper-case letter.
 * The output is returned as a vector of rows, each row being a std::string.
 *
 * Pre-condition:
 *   letter is in the range 'A' … 'Z' (inclusive). A std::invalid_argument
 *   exception is thrown otherwise.
 */
DIAMOND_NODISCARD auto create_diamond(char letter) -> std::vector<std::string>;
DIAMOND_NODISCARD auto rows(char letter) -> std::vector<std::string>;

/*
 * create_diamond_string
 *
 * Same as create_diamond() but returns the diamond as a single string with
 * newline separators.  The terminating newline is omitted.
 */
DIAMOND_NODISCARD auto create_diamond_string(char letter) -> std::string;

}  // namespace diamond
