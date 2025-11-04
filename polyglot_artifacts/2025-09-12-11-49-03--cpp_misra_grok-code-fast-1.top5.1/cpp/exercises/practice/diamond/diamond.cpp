#include "diamond.h"

#include <string>
#include <vector>
#include <cstdint>
#include <char_traits>

namespace diamond {

std::vector<std::string> rows(const char letter) {
    const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::int32_t index = static_cast<std::int32_t>(std::char_traits<char>::to_int_type(letter) - std::char_traits<char>::to_int_type('A'));
    std::int32_t size = (2 * index) + 1;
    std::vector<std::string> result;
    for (std::int32_t row = 0; row < size; ++row) {
        std::int32_t dist = (row < index) ? row : (size - 1 - row);
        std::int32_t pos = (row <= index) ? row : (size - 1 - row);
        char current = letters[pos];
        std::string line(static_cast<std::size_t>(size), ' ');
        line[static_cast<std::size_t>(index - dist)] = current;
        if (dist > 0) {
            line[static_cast<std::size_t>(index + dist)] = current;
        }
        result.push_back(line);
    }
    return result;
}

}  // namespace diamond
