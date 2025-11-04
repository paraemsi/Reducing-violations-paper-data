#include "diamond.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

static constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//  Helper: locate the zero-based position of the requested letter
static uint_t letter_index(const char letter)
{
    for (uint_t idx = 0U; alphabet[idx] != '\0'; ++idx)
    {
        if (alphabet[idx] == letter)
        {
            return idx;
        }
    }
    throw std::invalid_argument("letter must be between 'A' and 'Z'");
}

//  Build the diamond line collection
std::vector<std::string> make_lines(const char letter)
{
    const uint_t idxMax = letter_index(letter);
    const uint_t width  = (idxMax * static_cast<uint_t>(2)) + static_cast<uint_t>(1);

    std::vector<std::string> top;
    top.reserve(static_cast<std::size_t>(idxMax) + static_cast<std::size_t>(1));

    for (uint_t idx = 0U; idx <= idxMax; ++idx)
    {
        const uint_t leading = idxMax - idx;
        std::string  row(static_cast<std::string::size_type>(width), ' ');

        const char current = alphabet[idx];

        row[static_cast<std::string::size_type>(leading)] = current;

        if (idx != 0U)
        {
            const uint_t trailingPos = static_cast<uint_t>(width - leading - static_cast<uint_t>(1));
            row[static_cast<std::string::size_type>(trailingPos)] = current;
        }

        top.push_back(row);
    }

    std::vector<std::string> result = top;

    //  Append the bottom half (reverse of top without the middle row)
    for (std::size_t i = static_cast<std::size_t>(idxMax); i > static_cast<std::size_t>(0); --i)
    {
        result.push_back(top[i - static_cast<std::size_t>(1)]);
    }

    return result;
}

std::vector<std::string> rows(const char letter)
{
    //  Wrapper retained for backward-compatibility with test-suite
    return make_lines(letter);
}

//  Build the complete string representation with '\n' separators
std::string make(const char letter)
{
    const std::vector<std::string> rows = make_lines(letter);

    std::string output;
    if (!rows.empty())
    {
        output.reserve(rows.size() * (rows[0].size() + static_cast<std::size_t>(1)));
    }

    for (std::size_t i = static_cast<std::size_t>(0); i < rows.size(); ++i)
    {
        output += rows[i];
        if ((i + static_cast<std::size_t>(1)) != rows.size())
        {
            output += '\n';
        }
    }

    return output;
}

}  // namespace diamond
