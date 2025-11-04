#include "diamond.h"
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

namespace {
using char_alias = char;
using size_alias = std::uint32_t;

size_alias get_diamond_size(char_alias letter) {
    // 'A' is 65 in ASCII
    // Size = 2 * (letter - 'A') + 1
    return (static_cast<size_alias>(2U) * static_cast<size_alias>(letter - static_cast<char_alias>('A'))) + static_cast<size_alias>(1U);
}

std::string make_row(char_alias letter, char_alias current, size_alias diamond_size) {
    size_alias n = static_cast<size_alias>(letter - static_cast<char_alias>('A'));
    size_alias row = static_cast<size_alias>(current - static_cast<char_alias>('A'));
    size_alias leading_spaces = n - row;
    std::string result;

    // Leading spaces
    result.append(leading_spaces, ' ');

    // First letter
    result += static_cast<char>(current);

    if(row != static_cast<size_alias>(0U)) {
        // Inner spaces
        size_alias inner_spaces = (static_cast<size_alias>(2U) * row) - static_cast<size_alias>(1U);
        result.append(inner_spaces, ' ');
        // Second letter
        result += static_cast<char>(current);
    }

    // Trailing spaces
    result.append(leading_spaces, ' ');

    return result;
}
} // anonymous namespace

std::vector<std::string> make_diamond(char letter) {
    std::vector<std::string> result;
    if((letter < static_cast<char>('A')) || (letter > static_cast<char>('Z'))) {
        // Return empty for invalid input
        return result;
    }
    size_alias diamond_size = get_diamond_size(letter);

    // Top half (including middle)
    for(char_alias c = static_cast<char_alias>('A'); c <= letter; ++c) {
        result.push_back(make_row(letter, c, diamond_size));
    }
    // Bottom half
    for(char_alias c = static_cast<char_alias>(letter - 1); c >= static_cast<char_alias>('A'); --c) {
        result.push_back(make_row(letter, c, diamond_size));
        if(c == static_cast<char_alias>('A')) {
            break;
        }
    }
    return result;
}

std::vector<std::string> rows(char letter) {
    return make_diamond(letter);
}

}  // namespace diamond
