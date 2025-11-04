#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> result;
    
    // Handle 'A' case
    if (letter == 'A') {
        result.push_back("A");
        return result;
    }
    
    // Calculate dimensions
    const std::int32_t diff = static_cast<std::int32_t>(letter) - static_cast<std::int32_t>('A');
    const std::int32_t size = (2 * diff) + 1;
    
    // Generate top half including the middle
    for (std::int32_t i = 0; i <= diff; i++) {
        std::string row(size, ' ');
        const char current_char = static_cast<char>('A' + i);
        const std::int32_t left_pos = diff - i;
        const std::int32_t right_pos = diff + i;
        row[left_pos] = current_char;
        row[right_pos] = current_char;
        result.push_back(row);
    }
    
    // Generate bottom half by mirroring the top part (excluding the middle)
    for (std::int32_t i = (diff - 1); i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
