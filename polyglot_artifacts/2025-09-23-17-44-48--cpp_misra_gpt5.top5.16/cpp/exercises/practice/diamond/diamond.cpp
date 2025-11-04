#include "diamond.h"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> rows(char letter)
{
    const std::string uppercase_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string lowercase_alphabet = "abcdefghijklmnopqrstuvwxyz";

    std::size_t pos = uppercase_alphabet.find(letter);
    if (pos == std::string::npos)
    {
        pos = lowercase_alphabet.find(letter);
    }
    if (pos == std::string::npos)
    {
        throw std::invalid_argument("diamond: input must be a letter A-Z or a-z");
    }

    const std::size_t max_index = pos;
    const std::size_t width = ((static_cast<std::size_t>(2) * max_index) + static_cast<std::size_t>(1));

    std::vector<std::string> out;
    const std::size_t height = ((static_cast<std::size_t>(2) * max_index) + static_cast<std::size_t>(1));
    out.reserve(height);

    for (std::size_t row = static_cast<std::size_t>(0); row < (max_index + static_cast<std::size_t>(1)); ++row)
    {
        const char ch = uppercase_alphabet[row];
        std::string line(width, ' ');

        const std::size_t leading = (max_index - row);
        line[leading] = ch;
        const std::size_t right = ((width - static_cast<std::size_t>(1)) - leading);
        if (right != leading)
        {
            line[right] = ch;
        }

        out.push_back(line);
    }

    if (max_index != static_cast<std::size_t>(0))
    {
        for (std::size_t row = static_cast<std::size_t>(0); row < max_index; ++row)
        {
            const std::size_t top_row = ((max_index - static_cast<std::size_t>(1)) - row);
            const char ch = uppercase_alphabet[top_row];
            std::string line(width, ' ');

            const std::size_t leading = (max_index - top_row);
            line[leading] = ch;
            const std::size_t right = ((width - static_cast<std::size_t>(1)) - leading);
            if (right != leading)
            {
                line[right] = ch;
            }

            out.push_back(line);
        }
    }

    return out;
}

std::string make(char letter)
{
    const std::vector<std::string> lines = rows(letter);
    if (lines.empty())
    {
        return std::string();
    }

    std::string result;
    const std::size_t width = lines[static_cast<std::size_t>(0)].size();
    const std::size_t count = lines.size();
    const std::size_t newlines = (count - static_cast<std::size_t>(1));
    const std::size_t capacity = ((width * count) + newlines);
    result.reserve(capacity);

    for (std::size_t i = static_cast<std::size_t>(0); i < count; ++i)
    {
        result.append(lines[i]);
        if (i != (count - static_cast<std::size_t>(1)))
        {
            result.push_back('\n');
        }
    }

    return result;
}

}  // namespace diamond
