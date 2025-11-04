#include "diamond.h"

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

[[nodiscard]] auto create_diamond(char letter) -> std::string
{
    const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    /* Validate input */
    if (alphabet.find(letter) == std::string::npos) {
        throw std::invalid_argument("Letter must be an uppercase A-Z");
    }

    const std::size_t index{alphabet.find(letter)};
    const std::size_t dimension{
        (index * static_cast<std::size_t>(2U)) + static_cast<std::size_t>(1U)
    };

    std::string output{};
    /* Reserve enough space: each line plus a newline, approximated */
    output.reserve(dimension * (dimension + static_cast<std::size_t>(1U)));

    /* Build the top half (including the middle line) */
    for (std::size_t i{0U}; i <= index; ++i) {
        const char current{alphabet[i]};

        std::string line(dimension, ' ');
        const std::size_t leftPos{index - i};
        const std::size_t rightPos{index + i};

        line[leftPos] = current;
        line[rightPos] = current;

        output += line;
        output += (i == index) ? "" : "\n";
    }

    /* Build the bottom half (mirror of the top, excluding the middle line) */
    for (std::size_t i{index}; i > 0U; --i) {
        const std::size_t mirrorIdx{i - static_cast<std::size_t>(1U)};
        const char current{alphabet[mirrorIdx]};

        std::string line(dimension, ' ');
        const std::size_t leftPos{index - mirrorIdx};
        const std::size_t rightPos{index + mirrorIdx};

        line[leftPos] = current;
        line[rightPos] = current;

        output += "\n";
        output += line;
    }

    output += '\n';
    return output;
}

[[nodiscard]] auto rows(char letter) -> std::vector<std::string>
{
    const std::string diamond_str{create_diamond(letter)};
    std::vector<std::string> lines{};
    std::size_t start{0U};

    while (true) {
        const std::size_t pos{diamond_str.find('\n', start)};
        if (pos == std::string::npos) {
            break;
        }
        lines.emplace_back(diamond_str.substr(start, pos - start));
        start = pos + static_cast<std::size_t>(1U);
    }

    return lines;
}

}  // namespace diamond
