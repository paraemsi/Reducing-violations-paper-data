#include "diamond.h"

#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

static auto build_line(const std::int32_t distance,
                       const std::int32_t size) -> std::string
{
    const std::int32_t width = ((size * 2) + 1);

    std::string line(static_cast<std::size_t>(width), ' ');

    const std::int32_t left_index  = size - distance;
    const std::int32_t right_index = size + distance;

    const std::int32_t a_code      = std::char_traits<char>::to_int_type('A');
    const std::int32_t row_code    = a_code + distance;
    const char row_char            = std::char_traits<char>::to_char_type(row_code);

    line[static_cast<std::size_t>(left_index)]  = row_char;
    line[static_cast<std::size_t>(right_index)] = row_char;

    return line;
}

/* Return each row of the diamond as a separate string */
auto rows(char letter) -> std::vector<std::string>
{
    const std::int32_t letter_code = std::char_traits<char>::to_int_type(letter);
    const std::int32_t a_code      = std::char_traits<char>::to_int_type('A');
    const std::int32_t z_code      = std::char_traits<char>::to_int_type('Z');

    if ((letter_code < a_code) || (letter_code > z_code))
    {
        return {};
    }

    const std::int32_t size   = letter_code - a_code;
    const std::int32_t height = ((size * 2) + 1);

    std::vector<std::string> lines;
    lines.reserve(static_cast<std::size_t>(height));

    /* Top half including the middle line */
    for (std::int32_t distance = 0; distance <= size; ++distance)
    {
        lines.push_back(build_line(distance, size));
    }

    /* Bottom half */
    for (std::int32_t distance = (size - 1); distance >= 0; --distance)
    {
        lines.push_back(build_line(distance, size));
    }

    return lines;
}

auto make(char letter) -> std::string
{
    const auto lines = rows(letter);

    std::string result;
    for (std::size_t idx = 0U; idx < lines.size(); ++idx)
    {
        result += lines[idx];
        if ((idx + 1U) < lines.size())
        {
            result += '\n';
        }
    }

    return result;
}

}  // namespace diamond
