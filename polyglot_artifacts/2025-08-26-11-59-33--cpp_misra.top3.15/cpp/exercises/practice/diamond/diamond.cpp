#include "diamond.h"

#include <cstddef>  // for std::size_t

namespace diamond {

diamond_lines_t make_diamond(diamond_char_t c)
{
    // Only uppercase A-Z allowed
    if((c < 'A') || (c > 'Z')) {
        return diamond_lines_t();
    }

    // Calculate diamond size
    std::uint8_t n = static_cast<std::uint8_t>(c - 'A');
    std::uint8_t size = static_cast<std::uint8_t>((n * 2U) + 1U);

    diamond_lines_t lines;
    lines.reserve(size);

    for(std::uint8_t i = 0U; i < size; ++i) {
        std::uint8_t row = (i <= n) ? i : static_cast<std::uint8_t>((size - 1U) - i);
        diamond_char_t letter = static_cast<diamond_char_t>('A' + row);

        std::uint8_t outer_spaces = static_cast<std::uint8_t>(n - row);
        std::uint8_t inner_spaces = static_cast<std::uint8_t>((row == 0U) ? 0U : (row * 2U - 1U));

        diamond_string_t line;
        line.reserve(size);

        // Leading spaces
        for(std::uint8_t s = 0U; s < outer_spaces; ++s) {
            line.push_back(' ');
        }

        // First letter
        line.push_back(letter);

        // Inner spaces and second letter (if not 'A')
        if(row != 0U) {
            for(std::uint8_t s = 0U; s < inner_spaces; ++s) {
                line.push_back(' ');
            }
            line.push_back(letter);
        }

        // Trailing spaces
        for(std::uint8_t s = 0U; s < outer_spaces; ++s) {
            line.push_back(' ');
        }

        lines.push_back(line);
    }

    return lines;
}

}  // namespace diamond
