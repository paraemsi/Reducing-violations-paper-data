#include "diamond.h"

#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

std::string make_diamond(char letter)
{
    // Reference alphabets for position lookup (no arithmetic or relational ops on chars)
    constexpr char UPPER[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    constexpr char LOWER[27] = "abcdefghijklmnopqrstuvwxyz";
    constexpr std::size_t ALPHA_LEN = static_cast<std::size_t>(26);

    // Find index of the letter (case-insensitive) using only equality checks
    std::size_t pos = static_cast<std::size_t>(0);
    bool found = false;

    for (std::size_t i = static_cast<std::size_t>(0); (i < ALPHA_LEN); ++i)
    {
        if (UPPER[i] == letter)
        {
            pos = i;
            found = true;
            break;
        }
        else
        {
            if (LOWER[i] == letter)
            {
                pos = i;
                found = true;
                break;
            }
            else
            {
                // continue
            }
        }
    }

    if (!found)
    {
        // Not an alphabetic character; return empty result per contract
        return std::string();
    }

    const std::size_t n = pos;
    const std::size_t width = (static_cast<std::size_t>(2) * n) + static_cast<std::size_t>(1);
    std::string result;
    result.reserve(((width * width) + width));  // heuristic reservation

    for (std::size_t row = static_cast<std::size_t>(0); (row < width); ++row)
    {
        // Determine which letter index this row uses, mirroring around the center
        std::size_t j = row;
        if (row > n)
        {
            j = ((static_cast<std::size_t>(2) * n) - row);
        }
        else
        {
            // keep j as row
        }

        const std::size_t left = (n - j);
        const std::size_t right = (n + j);

        std::string line(width, ' ');
        const char ch = UPPER[j];

        line[left] = ch;
        line[right] = ch;

        result += line;
        if (((row + static_cast<std::size_t>(1)) < width))
        {
            result += '\n';
        }
        else
        {
            // last line: no trailing newline
        }
    }

    return result;
}

std::vector<std::string> rows(char letter)
{
    // Reference alphabets for position lookup (no arithmetic or relational ops on chars)
    constexpr char UPPER[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    constexpr char LOWER[27] = "abcdefghijklmnopqrstuvwxyz";
    constexpr std::size_t ALPHA_LEN = static_cast<std::size_t>(26);

    // Find index of the letter (case-insensitive) using only equality checks
    std::size_t pos = static_cast<std::size_t>(0);
    bool found = false;

    for (std::size_t i = static_cast<std::size_t>(0); (i < ALPHA_LEN); ++i)
    {
        if (UPPER[i] == letter)
        {
            pos = i;
            found = true;
            break;
        }
        else
        {
            if (LOWER[i] == letter)
            {
                pos = i;
                found = true;
                break;
            }
            else
            {
                // continue
            }
        }
    }

    if (!found)
    {
        // Not an alphabetic character; return empty result per contract
        return std::vector<std::string>();
    }

    const std::size_t n = pos;
    const std::size_t width = (static_cast<std::size_t>(2) * n) + static_cast<std::size_t>(1);
    std::vector<std::string> result;
    result.reserve(width);

    for (std::size_t row = static_cast<std::size_t>(0); (row < width); ++row)
    {
        // Determine which letter index this row uses, mirroring around the center
        std::size_t j = row;
        if (row > n)
        {
            j = ((static_cast<std::size_t>(2) * n) - row);
        }
        else
        {
            // keep j as row
        }

        const std::size_t left = (n - j);
        const std::size_t right = (n + j);

        std::string line(width, ' ');
        const char ch = UPPER[j];

        line[left] = ch;
        line[right] = ch;

        result.push_back(line);
    }

    return result;
}

}  // namespace diamond
