#include "diamond.h"

#include <stdexcept>

namespace diamond {

Lines make(char const letter)
{
    // Alphabet reference to avoid any arithmetic on character codes.
    static constexpr char kAlphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Find the index of the requested letter within the alphabet.
    std::size_t pos = std::size_t{0};
    while ((pos < std::size_t{26}) && (kAlphabet[pos] != letter)) {
        ++pos;
    }

    if (pos == std::size_t{26}) {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const std::size_t width = (pos * std::size_t{2}) + std::size_t{1};
    const std::size_t center = pos;

    Lines lines{};
    lines.reserve((pos * std::size_t{2}) + std::size_t{1});

    // Top half including the middle line.
    for (std::size_t i = std::size_t{0}; (i <= pos); ++i) {
        const char row_ch = kAlphabet[i];
        std::string line(width, ' ');

        if (i == std::size_t{0}) {
            line[center] = row_ch;
        } else {
            const std::size_t left = center - i;
            const std::size_t right = center + i;
            line[left] = row_ch;
            line[right] = row_ch;
        }

        lines.push_back(line);
    }

    // Bottom half (mirror without duplicating the middle line).
    if (pos > std::size_t{0}) {
        for (std::size_t i = pos; (i > std::size_t{0}); --i) {
            lines.push_back(lines[i - std::size_t{1}]);
        }
    }

    return lines;
}

Lines rows(char const letter)
{
    return make(letter);
}

}  // namespace diamond
