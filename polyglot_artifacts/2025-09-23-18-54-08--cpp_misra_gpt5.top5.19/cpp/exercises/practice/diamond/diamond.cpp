#include "diamond.h"

#include <array>
#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

namespace {
constexpr std::array<char, 26U> UPPER{
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};
constexpr std::array<char, 26U> LOWER{
    'a','b','c','d','e','f','g','h','i','j','k','l','m',
    'n','o','p','q','r','s','t','u','v','w','x','y','z'
};

bool find_index(char letter, std::size_t& out_index)
{
    for (std::size_t i = 0U; (i < UPPER.size()); ++i) {
        if ((letter == UPPER[i]) || (letter == LOWER[i])) {
            out_index = i;
            return true;
        }
    }
    return false;
}

std::string build_line(std::size_t row, std::size_t max_row)
{
    // row in [0, max_row]
    const std::size_t outer_spaces = (max_row - row);
    std::string s{};
    s.reserve(((outer_spaces * 2U) + 1U) + ((row == 0U) ? 0U : (((2U * row) - 1U) + 1U)));

    s.append(outer_spaces, ' ');

    const char ch = UPPER[row];
    s.push_back(ch);

    if (row != 0U) {
        const std::size_t inner_spaces = ((2U * row) - 1U);
        s.append(inner_spaces, ' ');
        s.push_back(ch);
    }

    s.append(outer_spaces, ' ');
    return s;
}
}  // namespace

std::vector<std::string> rows(char letter)
{
    std::size_t idx = 0U;
    if (!find_index(letter, idx)) {
        return std::vector<std::string>{};
    }

    const std::size_t max_row = idx;
    const std::size_t total_lines = ((2U * max_row) + 1U);
    std::vector<std::string> lines{};
    lines.reserve(total_lines);

    for (std::size_t r = 0U; (r <= max_row); ++r) {
        lines.emplace_back(build_line(r, max_row));
    }
    for (std::size_t r = max_row; (r > 0U); --r) {
        lines.emplace_back(build_line((r - 1U), max_row));
    }

    return lines;
}

std::string make(char letter)
{
    const std::vector<std::string> ls = rows(letter);
    if (ls.empty()) {
        return std::string{};
    }

    std::string result{};
    // Precompute approximate size: sum of line sizes + newlines between
    std::size_t approx = 0U;
    for (std::size_t i = 0U; (i < ls.size()); ++i) {
        approx += ls[i].size();
    }
    approx += (ls.empty() ? 0U : (ls.size() - 1U));
    result.reserve(approx);

    for (std::size_t i = 0U; (i < ls.size()); ++i) {
        result += ls[i];
        if (((i + 1U) < ls.size())) {
            result.push_back('\n');
        }
    }

    return result;
}

}  // namespace diamond
