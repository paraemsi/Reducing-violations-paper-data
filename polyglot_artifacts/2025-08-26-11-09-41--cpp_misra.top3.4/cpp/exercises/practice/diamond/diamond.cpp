#include "diamond.h"

#include <string>
#include <vector>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char_t c)
{
    // Only uppercase letters allowed
    if((c < 'A') || (c > 'Z')) {
        return std::vector<std::string>();
    }

    size_t_t n = static_cast<size_t_t>(c - 'A');
    size_t_t width = (n * 2U) + 1U;
    std::vector<std::string> result;

    for(size_t_t i = 0U; i <= n; ++i) {
        std::string row(width, ' ');
        char_t letter = static_cast<char_t>('A' + static_cast<char_t>(i));
        size_t_t left = n - i;
        size_t_t right = n + i;
        row[left] = letter;
        row[right] = letter;
        result.push_back(row);
    }
    // Mirror the top half (excluding the middle row)
    for(size_t_t i = n; i-- > 0U;) {
        result.push_back(result[i]);
    }
    return result;
}

}  // namespace diamond
