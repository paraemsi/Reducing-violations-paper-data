#include "diamond.h"
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

using DiamondString = std::vector<std::string>;

static std::uint32_t get_alpha_index(char letter)
{
    // Assumes input is uppercase A-Z
    return static_cast<std::uint32_t>(letter - 'A');
}

DiamondString make_diamond(char letter)
{
    // Defensive: Only allow uppercase A-Z
    if((letter < 'A') || (letter > 'Z'))
    {
        return DiamondString();
    }

    const std::uint32_t n = get_alpha_index(letter);
    const std::uint32_t size = (2U * n) + 1U;
    DiamondString result;
    result.reserve(size);

    for(std::uint32_t i = 0U; i < size; ++i)
    {
        std::uint32_t row = (i <= n) ? i : (size - 1U - i);
        char ch = static_cast<char>('A' + row);

        std::uint32_t outer_spaces = n - row;
        std::uint32_t inner_spaces = (row == 0U) ? 0U : (2U * row - 1U);

        std::string line;
        line.reserve(size);

        // Leading spaces
        line.append(outer_spaces, ' ');

        // First letter
        line += ch;

        // Inner spaces and second letter (if not 'A')
        if(row != 0U)
        {
            line.append(inner_spaces, ' ');
            line += ch;
        }

        // Trailing spaces
        line.append(outer_spaces, ' ');

        result.push_back(line);
    }

    return result;
}

}  // namespace diamond
