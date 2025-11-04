#include "diamond.h"

#include <cstdint>
#include <stdexcept>

namespace diamond {

auto build(char letter) -> std::vector<std::string>
{
    // Convert characters to their integer representations – compliant with MISRA rules.
    const std::int32_t a_code{std::char_traits<char>::to_int_type('A')};
    const std::int32_t letter_code{std::char_traits<char>::to_int_type(letter)};

    // Ensure the input is within the accepted range.
    if ((letter_code < a_code) || (letter_code > (a_code + std::int32_t{25}))) {
        throw std::invalid_argument("letter must be in range 'A'..'Z'");
    }
    const std::int32_t distance{letter_code - a_code};

    // The diamond is a square: side length = (2 * distance) + 1.
    const std::int32_t side_len{(2 * distance) + 1};

    std::vector<std::string> lines{};
    lines.reserve(static_cast<std::size_t>(side_len));

    // Build the top half (including the middle row).
    for (std::int32_t row{0}; row <= distance; ++row) {
        const std::int32_t leading_spaces{distance - row};
        const std::int32_t inner_spaces{(row == 0) ? 0 : ((row * 2) - 1)};

        // Determine the current letter.
        const char current_letter{
            std::char_traits<char>::to_char_type(a_code + row)};

        std::string line{};
        line.reserve(static_cast<std::size_t>(side_len));

        line.append(static_cast<std::size_t>(leading_spaces), ' ');
        line.push_back(current_letter);

        if (row != 0) {
            line.append(static_cast<std::size_t>(inner_spaces), ' ');
            line.push_back(current_letter);
        }

        line.append(static_cast<std::size_t>(leading_spaces), ' ');

        lines.push_back(line);
    }

    // Build the bottom half (mirror of the top, excluding the middle row).
    for (std::int32_t row{distance - 1}; row >= 0; --row) {
        lines.push_back(lines[static_cast<std::size_t>(row)]);
    }

    return lines;
}

auto rows(char letter) -> std::vector<std::string>
{
    return build(letter);
}

}  // namespace diamond
