#include "diamond.h"
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

DiamondString make_diamond(char letter)
{
    // Validate input: must be uppercase A-Z
    if((letter < 'A') || (letter > 'Z'))
    {
        return DiamondString();
    }

    // Calculate size
    std::uint32_t n = static_cast<std::uint32_t>(letter - 'A');
    std::uint32_t size = (n * 2U) + 1U;

    DiamondString result;
    result.reserve(size);

    for(std::uint32_t i = 0U; i < size; ++i)
    {
        std::uint32_t row = (i <= n) ? i : (size - 1U - i);
        char ch = static_cast<char>('A' + row);

        std::uint32_t outer_spaces = n - row;
        std::uint32_t inner_spaces = (row == 0U) ? 0U : ((row * 2U) - 1U);

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
