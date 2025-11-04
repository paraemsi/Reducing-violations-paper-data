#include "diamond.h"
#include <string>
#include <vector>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    // Handle 'A' case directly
    if (letter == 'A') {
        return {"A"};
    }
    
    // Convert input to a number
    const std::int32_t diff = static_cast<std::int32_t>(letter) - static_cast<std::int32_t>('A');
    const std::int32_t size = (2 * diff) + 1;
    std::vector<std::string> result;
    
    // Generate each line
    for (std::int32_t i = 0; i <= diff; i++) {
        std::string row(static_cast<size_t>(size), ' ');
        const char current_char = static_cast<char>('A' + i);
        const std::int32_t left_idx = diff - i;
        const std::int32_t right_idx = diff + i;
        row[static_cast<size_t>(left_idx)] = current_char;
        row[static_cast<size_t>(right_idx)] = current_char;
        result.push_back(row);
    }
    
    // Add the bottom part by mirroring (excluding the middle)
    for (std::int32_t i = diff - 1; i >= 0; i--) {
        result.push_back(result[static_cast<size_t>(i)]);
    }
    
    return result;
}

}  // namespace diamond
