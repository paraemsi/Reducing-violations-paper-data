#include "diamond.h"
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

namespace {
using char_alias = char;
using size_alias = std::uint32_t;

[[nodiscard]] size_alias get_diamond_size(char_alias letter) {
    // 'A' is 0, so add 1 for size
    return static_cast<size_alias>((static_cast<size_alias>(letter) - static_cast<size_alias>('A')) * 2U + 1U);
}

[[nodiscard]] size_alias get_letter_index(char_alias letter) {
    return static_cast<size_alias>(letter) - static_cast<size_alias>('A');
}

[[nodiscard]] std::string make_row(char_alias letter, size_alias row, size_alias size) {
    size_alias idx = (row <= get_letter_index(letter)) ? row : (size - row - 1U);
    char_alias current = static_cast<char_alias>(static_cast<size_alias>('A') + idx);
    size_alias outer_spaces = get_letter_index(letter) - idx;
    size_alias inner_spaces = (idx == 0U) ? 0U : (idx * 2U - 1U);

    std::string result;
    result.reserve(size);

    // Leading spaces
    for (size_alias i = 0U; i < outer_spaces; ++i) {
        result += ' ';
    }

    // First letter
    result += current;

    // Inner spaces and second letter (if not 'A')
    if (inner_spaces > 0U) {
        for (size_alias i = 0U; i < inner_spaces; ++i) {
            result += ' ';
        }
        result += current;
    }

    // Trailing spaces
    for (size_alias i = 0U; i < outer_spaces; ++i) {
        result += ' ';
    }

    return result;
}
} // anonymous namespace

std::vector<std::string> make_diamond(char letter) noexcept {
    std::vector<std::string> diamond_rows;
    size_alias size = get_diamond_size(letter);
    diamond_rows.reserve(size);

    for (size_alias row = 0U; row < size; ++row) {
        diamond_rows.push_back(make_row(letter, row, size));
    }
    return diamond_rows;
}

}  // namespace diamond
