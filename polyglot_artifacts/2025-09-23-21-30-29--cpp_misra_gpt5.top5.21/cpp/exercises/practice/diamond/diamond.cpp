#include "diamond.h"
#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

namespace {
constexpr std::array<char, 26U> kAlphabet{
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

auto find_index(const char letter) -> std::size_t
{
    for (std::size_t i = static_cast<std::size_t>(0); (i < kAlphabet.size()); ++i) {
        if ((kAlphabet[i] == letter)) {
            return i;
        }
    }
    throw std::invalid_argument("letter must be an uppercase Latin letter A-Z");
}

auto make_line(const std::size_t alpha_index, const std::size_t max_index) -> std::string
{
    const std::size_t leading = (max_index - alpha_index);
    const std::size_t inner = (alpha_index == static_cast<std::size_t>(0))
        ? static_cast<std::size_t>(0)
        : ((static_cast<std::size_t>(2) * alpha_index) - static_cast<std::size_t>(1));
    const std::size_t width = ((static_cast<std::size_t>(2) * max_index) + static_cast<std::size_t>(1));

    std::string line;
    line.reserve(width);

    line.append(leading, ' ');
    line.push_back(kAlphabet[alpha_index]);
    if ((alpha_index != static_cast<std::size_t>(0))) {
        line.append(inner, ' ');
        line.push_back(kAlphabet[alpha_index]);
    }
    line.append(leading, ' ');
    return line;
}
}  // namespace

auto make(const char letter) -> std::string
{
    const std::size_t idx = find_index(letter);
    const std::size_t height = ((static_cast<std::size_t>(2) * idx) + static_cast<std::size_t>(1));
    const std::size_t width = ((static_cast<std::size_t>(2) * idx) + static_cast<std::size_t>(1));
    const std::size_t last_top_row = idx;

    std::string output;
    output.reserve((height * (width + static_cast<std::size_t>(1))));

    for (std::size_t row = static_cast<std::size_t>(0); (row <= last_top_row); ++row) {
        output += make_line(row, idx);
        output.push_back('\n');
    }

    for (std::size_t r = last_top_row; (r > static_cast<std::size_t>(0)); --r) {
        const std::size_t row = (r - static_cast<std::size_t>(1));
        output += make_line(row, idx);
        if ((row != static_cast<std::size_t>(0))) {
            output.push_back('\n');
        }
    }

    return output;
}

auto rows(const char letter) -> std::vector<std::string>
{
    const std::size_t idx = find_index(letter);
    const std::size_t last_top_row = idx;
    const std::size_t height = ((static_cast<std::size_t>(2) * idx) + static_cast<std::size_t>(1));

    std::vector<std::string> output;
    output.reserve(height);

    for (std::size_t row = static_cast<std::size_t>(0); (row <= last_top_row); ++row) {
        output.push_back(make_line(row, idx));
    }

    for (std::size_t r = last_top_row; (r > static_cast<std::size_t>(0)); --r) {
        const std::size_t row_index = (r - static_cast<std::size_t>(1));
        output.push_back(make_line(row_index, idx));
    }

    return output;
}

}  // namespace diamond
