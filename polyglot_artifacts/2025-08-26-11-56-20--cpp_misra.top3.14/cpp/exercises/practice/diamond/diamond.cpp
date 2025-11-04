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
    std::string result(size, ' ');
    size_alias idx = (row <= get_letter_index(letter)) ? row : (size - row - 1U);
    char_alias ch = static_cast<char_alias>(static_cast<size_alias>('A') + idx);
    size_alias outer_spaces = get_letter_index(letter) - idx;
    size_alias inner_spaces = (idx == 0U) ? 0U : (idx * 2U - 1U);

    if (idx == 0U) {
        result.at(outer_spaces) = 'A';
    } else {
        result.at(outer_spaces) = ch;
        result.at(size - outer_spaces - 1U) = ch;
    }
    return result;
}
} // anonymous namespace

std::vector<std::string> rows(char letter) {
    size_alias size = get_diamond_size(letter);
    std::vector<std::string> diamond_vec;
    diamond_vec.reserve(size);

    for (size_alias row = 0U; row < size; ++row) {
        diamond_vec.push_back(make_row(letter, row, size));
    }
    return diamond_vec;
}

}  // namespace diamond
