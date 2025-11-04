#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace diamond {

using diamond_char_t = char;
using diamond_string_t = std::string;
using diamond_lines_t = std::vector<diamond_string_t>;

/**
 * @brief Generate a diamond shape as a vector of strings, given a capital letter.
 * 
 * @param c The widest point letter (must be 'A'..'Z')
 * @return diamond_lines_t The diamond, each string is a line.
 */
diamond_lines_t make_diamond(diamond_char_t c);

// Alias for compatibility with tests
inline diamond_lines_t rows(diamond_char_t c) { return make_diamond(c); }

}  // namespace diamond
