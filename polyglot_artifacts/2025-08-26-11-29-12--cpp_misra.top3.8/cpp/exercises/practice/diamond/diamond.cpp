#include "diamond.h"
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

using DiamondString = std::vector<std::string>;

static std::uint32_t get_diamond_size(char letter)
{
    // 'A' is 65 in ASCII
    // For 'A', size = 1; for 'B', size = 3; for 'C', size = 5, etc.
    std::uint32_t n = static_cast<std::uint32_t>(letter - 'A');
    return ((n * 2U) + 1U);
}

DiamondString make_diamond(char letter)
{
    DiamondString result;
    if((letter < 'A') || (letter > 'Z'))
    {
        // Return empty for invalid input
        return result;
    }

    std::uint32_t size = get_diamond_size(letter);
    std::uint32_t mid = (size / 2U);

    for(std::uint32_t i = 0U; i < size; ++i)
    {
        std::string row(size, ' ');
        std::uint32_t dist = (i <= mid) ? (mid - i) : (i - mid);
        char ch = static_cast<char>('A' + (mid - dist));
        std::uint32_t left = dist;
        std::uint32_t right = (size - dist - 1U);

        row[left] = ch;
        row[right] = ch;

        result.push_back(row);
    }

    return result;
}

}  // namespace diamond
