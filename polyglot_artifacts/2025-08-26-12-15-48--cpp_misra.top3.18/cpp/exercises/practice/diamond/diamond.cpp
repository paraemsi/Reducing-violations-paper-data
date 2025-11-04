#include "diamond.h"
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> make_diamond(char letter)
{
    // Only uppercase letters allowed
    if((letter < 'A') || (letter > 'Z')) {
        return std::vector<std::string>();
    }

    // Calculate size of diamond
    std::uint32_t n = static_cast<std::uint32_t>(letter - 'A');
    std::uint32_t size = (n * 2U) + 1U;
    std::vector<std::string> result;

    for(std::uint32_t i = 0U; i < size; ++i) {
        std::string row(size, ' ');
        std::uint32_t row_idx = (i <= n) ? i : (size - 1U - i);
        char ch = static_cast<char>('A' + row_idx);
        std::uint32_t left = n - row_idx;
        std::uint32_t right = n + row_idx;

        row[left] = ch;
        row[right] = ch;
        result.push_back(row);
    }

    return result;
}

}  // namespace diamond
