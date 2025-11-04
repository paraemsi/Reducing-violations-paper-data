#include "diamond.h"
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> make_diamond(char letter)
{
    // Only uppercase letters allowed
    if((letter < 'A') || (letter > 'Z'))
    {
        return std::vector<std::string>();
    }

    // Calculate size
    std::uint32_t n = static_cast<std::uint32_t>(letter - 'A');
    std::uint32_t size = (n * 2U) + 1U;
    std::vector<std::string> result;
    result.reserve(size);

    for(std::uint32_t i = 0U; i < size; ++i)
    {
        std::uint32_t row = (i <= n) ? i : (size - 1U - i);
        char ch = static_cast<char>('A' + row);
        std::uint32_t outer_spaces = n - row;
        std::uint32_t inner_spaces = (row == 0U) ? 0U : (row * 2U - 1U);

        std::string line;
        line.append(outer_spaces, ' ');
        line += ch;
        if(row != 0U)
        {
            line.append(inner_spaces, ' ');
            line += ch;
        }
        line.append(outer_spaces, ' ');
        result.push_back(line);
    }

    return result;
}

std::vector<std::string> rows(char letter)
{
    return make_diamond(letter);
}

}  // namespace diamond
