#pragma once

#include <string>
#include <vector>

namespace diamond {

 // Returns a vector of strings representing the diamond for the given uppercase letter.
 // Each string is a row of the diamond, including spaces.
[[nodiscard]] std::vector<std::string> make_diamond(char letter);

// Alias for test compatibility: rows is the required function name in tests.
inline std::vector<std::string> rows(char letter)
{
    return make_diamond(letter);
}

}  // namespace diamond
