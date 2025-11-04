#include "diamond.h"
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

typedef std::vector<std::string> DiamondString;

static std::uint32_t get_diamond_size(char letter)
{
    // 'A' is 0, so size = 2 * (letter - 'A') + 1
    return (static_cast<std::uint32_t>(2U) * (static_cast<std::uint32_t>(letter) - static_cast<std::uint32_t>('A')) + static_cast<std::uint32_t>(1U));
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
    std::uint32_t mid = (size - static_cast<std::uint32_t>(1U)) / static_cast<std::uint32_t>(2U);

    for(std::uint32_t i = 0U; i < size; ++i)
    {
        std::string row(size, ' ');
        std::uint32_t letter_idx = (i <= mid) ? i : (size - i - static_cast<std::uint32_t>(1U));
        char ch = static_cast<char>(static_cast<std::uint32_t>('A') + letter_idx);

        std::uint32_t left = mid - letter_idx;
        std::uint32_t right = mid + letter_idx;

        row[left] = ch;
        row[right] = ch;

        result.push_back(row);
    }
    return result;
}

}  // namespace diamond
