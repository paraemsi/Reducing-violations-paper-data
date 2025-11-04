#include "diamond.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
    constexpr std::array<char, 26U> alphabet{
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    auto index_of(char letter) -> std::uint32_t
    {
        for (std::uint32_t idx{0U}; idx < alphabet.size(); ++idx) {
            if (letter == alphabet[idx]) {
                return idx;
            }
        }
        throw std::invalid_argument{"letter must be between 'A' and 'Z'"};
    }

    auto letter_of(std::uint32_t idx) -> char
    {
        return alphabet[idx];
    }
} // unnamed namespace

namespace diamond {


auto make_diamond(char letter) -> std::vector<std::string>
{
    const std::uint32_t pos{index_of(letter)};
    const std::uint32_t size{(pos * 2U) + 1U};

    std::vector<std::string> rows;
    rows.reserve(size);

    for (std::uint32_t row{0U}; row < size; ++row) {
        const std::uint32_t mirror_row{
            (row <= pos) ? row : static_cast<std::uint32_t>((size - 1U) - row)};
        const std::uint32_t leading_spaces{pos - mirror_row};
        const std::uint32_t trailing_spaces{leading_spaces};
        const std::uint32_t inner_space{(mirror_row == 0U)
                                            ? 0U
                                            : ((mirror_row * 2U) - 1U)};
        const std::uint32_t row_length{
            leading_spaces + 1U + inner_space + 1U + trailing_spaces};

        std::string line(row_length, ' ');

        // left letter
        line[leading_spaces] = letter_of(mirror_row);

        if (mirror_row != 0U) {
            // right letter
            line[leading_spaces + 1U + inner_space] =
                letter_of(mirror_row);
        }

        // pad to full square width
        if (row_length < size) {
            line.append(size - row_length, ' ');
        }

        rows.emplace_back(line);
    }

    return rows;
}

auto to_string(char letter) -> std::string
{
    const auto rows{make_diamond(letter)};

    std::string result;
    for (std::uint32_t i{0U}; i < rows.size(); ++i) {
        result.append(rows[i]);
        if (i + 1U < rows.size()) {
            result.push_back('\n');
        }
    }
    return result;
}

}  // namespace diamond
