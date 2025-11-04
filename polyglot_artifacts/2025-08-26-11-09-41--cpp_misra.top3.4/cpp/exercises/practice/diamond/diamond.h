#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace diamond {

using char_t = char;
using size_t_t = std::size_t;

/// \brief Generate a diamond string for the given uppercase letter.
/// \param c The uppercase letter ('A'..'Z') to use as the widest point.
/// \return A vector of strings, each string is a row of the diamond.
std::vector<std::string> rows(char_t c);

}  // namespace diamond
