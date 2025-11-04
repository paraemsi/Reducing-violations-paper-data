#include "diamond.h"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace diamond {

auto make(char letter) -> std::vector<std::string> {
    static constexpr std::string_view kLetters("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    const std::size_t pos = kLetters.find(letter);
    if ((pos == std::string_view::npos)) {
        throw std::invalid_argument("letter must be an uppercase ASCII A-Z");
    }

    const std::size_t n = pos;
    const std::size_t height = ((n * static_cast<std::size_t>(2)) + static_cast<std::size_t>(1));
    const std::size_t width = height;

    std::vector<std::string> lines;
    lines.reserve(height);

    for (std::size_t i = static_cast<std::size_t>(0); i < height; ++i) {
        const std::size_t char_index = (i <= n) ? i : ((height - static_cast<std::size_t>(1)) - i);
        const std::size_t lead = (n - char_index);

        std::string row(width, ' ');
        const char ch = kLetters.at(char_index);

        const std::size_t left_pos = lead;
        const std::size_t right_pos = ((width - static_cast<std::size_t>(1)) - lead);

        row.at(left_pos) = ch;
        if (char_index != static_cast<std::size_t>(0)) {
            row.at(right_pos) = ch;
        } else {
            // Single 'A' in the first and last rows
        }

        lines.push_back(row);
    }

    return lines;
}

auto rows(char letter) -> std::vector<std::string> {
    return make(letter);
}

}  // namespace diamond
