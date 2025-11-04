#include "diamond.h"
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

// Implementation of the required rows() function.
DiamondString rows(char letter)
{
    // Validate input: must be between 'A' and 'Z'
    if((letter < 'A') || (letter > 'Z'))
    {
        return DiamondString();
    }

    std::uint32_t size = static_cast<std::uint32_t>(((letter - 'A') * 2U) + 1U);
    DiamondString result;
    result.reserve(size);

    for(std::uint32_t i = 0U; i < size; ++i)
    {
        std::uint32_t row = (i <= (size / 2U)) ? i : (size - 1U - i);
        char ch = static_cast<char>('A' + row);

        std::uint32_t outer_spaces = (size / 2U) - row;
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

// For backward compatibility, make_diamond just calls rows.
DiamondString make_diamond(char letter)
{
    return rows(letter);
}

}  // namespace diamond
