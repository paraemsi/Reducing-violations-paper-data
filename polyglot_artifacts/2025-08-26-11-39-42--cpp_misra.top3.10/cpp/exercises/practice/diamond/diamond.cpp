#include "diamond.h"

#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> make_diamond(char_t letter)
{
    // Only uppercase letters 'A' to 'Z' are supported
    if ((letter < 'A') || (letter > 'Z')) {
        return std::vector<std::string>();
    }

    size_t n = static_cast<size_t>(letter - 'A');
    size_t diamond_size = (n * 2U) + 1U;
    std::vector<std::string> result;

    for (size_t i = 0U; i <= (n * 2U); ++i) {
        size_t row = (i <= n) ? i : ((n * 2U) - i);
        char_t ch = static_cast<char_t>('A' + row);

        size_t outer_spaces = n - row;
        size_t inner_spaces = (row == 0U) ? 0U : ((row * 2U) - 1U);

        std::string line;
        // Leading spaces
        line.append(outer_spaces, ' ');
        // First letter
        line += ch;
        // Inner spaces and second letter (if not the first/last row)
        if (inner_spaces > 0U) {
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
