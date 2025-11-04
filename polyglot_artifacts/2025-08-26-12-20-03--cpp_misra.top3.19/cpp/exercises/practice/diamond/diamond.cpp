#include "diamond.h"
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

namespace {
using char_alias = char;
using size_alias = std::uint32_t;

[[nodiscard]] size_alias get_diamond_size(char_alias letter) {
    // 'A' is 0, so size = (letter - 'A') * 2 + 1
    return static_cast<size_alias>(((static_cast<size_alias>(letter) - static_cast<size_alias>('A')) * 2U) + 1U);
}

[[nodiscard]] size_alias get_letter_index(char_alias letter) {
    return static_cast<size_alias>(letter) - static_cast<size_alias>('A');
}
} // anonymous namespace

std::vector<std::string> make_diamond(char_alias letter) {
    const size_alias size = get_diamond_size(letter);
    std::vector<std::string> result;
    result.reserve(size);

    for (size_alias row = 0U; row < size; ++row) {
        std::string line(size, ' ');
        size_alias letter_idx;
        if (row <= (size / 2U)) {
            letter_idx = row;
        } else {
            letter_idx = (size - 1U) - row;
        }
        char_alias current_char = static_cast<char_alias>(static_cast<size_alias>('A') + letter_idx);
        size_alias left = (size / 2U) - letter_idx;
        size_alias right = (size / 2U) + letter_idx;

        line[left] = current_char;
        line[right] = current_char;
        result.push_back(line);
    }
    return result;
}

std::vector<std::string> rows(char letter) {
    return make_diamond(letter);
}

}  // namespace diamond
