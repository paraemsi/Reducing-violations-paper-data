#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace diamond {

using char_t = char;
typedef std::uint32_t size_t;

/// \brief Generate a diamond string for the given uppercase letter.
/// \param letter The uppercase letter ('A'..'Z') to be the widest point of the diamond.
/// \return A vector of strings, each string is a row of the diamond.
std::vector<std::string> make_diamond(char_t letter);

/// \brief Alias for make_diamond, used by tests.
/// \param letter The uppercase letter ('A'..'Z') to be the widest point of the diamond.
/// \return A vector of strings, each string is a row of the diamond.
inline std::vector<std::string> rows(char_t letter)
{
    return make_diamond(letter);
}

}  // namespace diamond
