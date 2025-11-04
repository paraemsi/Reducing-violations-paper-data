#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace diamond {

using char_t = char;
using string_t = std::string;
using string_vec_t = std::vector<string_t>;

/**
 * @brief Generate a diamond shape as a vector of strings, given a capital letter.
 * 
 * @param c The uppercase letter to use as the widest point of the diamond.
 * @return string_vec_t The diamond, each row as a string.
 */
string_vec_t make_diamond(char_t c);

// Alias for test compatibility: rows is the required function name in tests
inline string_vec_t rows(char_t c) { return make_diamond(c); }

}  // namespace diamond
