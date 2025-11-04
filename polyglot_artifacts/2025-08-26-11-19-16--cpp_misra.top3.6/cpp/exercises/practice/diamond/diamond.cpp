#include "diamond.h"

namespace diamond {

diamond::string_vec_t make_diamond(char_t c)
{
    // Only uppercase letters allowed
    if((c < 'A') || (c > 'Z'))
    {
        return diamond::string_vec_t();
    }

    // Calculate diamond size
    std::uint32_t n = static_cast<std::uint32_t>(c - 'A');
    std::uint32_t size = (n * 2U) + 1U;
    diamond::string_vec_t result;
    result.reserve(size);

    for(std::uint32_t i = 0U; i <= (n * 2U); ++i)
    {
        std::uint32_t row = (i <= n) ? i : ((n * 2U) - i);
        char_t letter = static_cast<char_t>('A' + row);

        std::uint32_t outer_spaces = n - row;
        std::uint32_t inner_spaces = (row == 0U) ? 0U : ((row * 2U) - 1U);

        diamond::string_t line;
        line.reserve(size);

        // Leading spaces
        for(std::uint32_t s = 0U; s < outer_spaces; ++s)
        {
            line.push_back(' ');
        }

        // First letter
        line.push_back(letter);

        // Inner spaces and second letter (if not 'A')
        if(row != 0U)
        {
            for(std::uint32_t s = 0U; s < inner_spaces; ++s)
            {
                line.push_back(' ');
            }
            line.push_back(letter);
        }

        // Trailing spaces
        for(std::uint32_t s = 0U; s < outer_spaces; ++s)
        {
            line.push_back(' ');
        }

        result.push_back(line);
    }

    return result;
}

}  // namespace diamond
