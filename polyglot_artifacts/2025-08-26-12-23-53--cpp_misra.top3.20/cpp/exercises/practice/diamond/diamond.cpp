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
    std::uint32_t n = static_cast<std::uint32_t>((letter - 'A') + 1U);
    std::uint32_t size = (2U * n) - 1U;

    DiamondString result;
    result.reserve(size);

    for(std::uint32_t i = 0U; i < size; ++i)
    {
        std::uint32_t row = (i < n) ? i : (size - 1U - i);
        char ch = static_cast<char>('A' + static_cast<char>(row));
        std::uint32_t outer_spaces = n - 1U - row;
        std::string line;

        // Leading spaces
        line.append(outer_spaces, ' ');

        // First letter
        line += ch;

        if(row != 0U)
        {
            // Inner spaces
            std::uint32_t inner_spaces = (2U * row) - 1U;
            line.append(inner_spaces, ' ');
            // Second letter
            line += ch;
        }

        // Trailing spaces
        line.append(outer_spaces, ' ');

        result.push_back(line);
    }

    return result;
}

}  // namespace diamond
