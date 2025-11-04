#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    // Number of rows is always odd: 2*(n) -1 where n is the number of unique letters
    const std::int32_t n = static_cast<std::int32_t>(letter - 'A' + 1);
    const std::int32_t size = (2 * n) - 1;
    
    std::vector<std::string> result;
    result.reserve(size);
    
    // Generate the top half including the middle
    for (std::int32_t i = 0; i < n; i++) {
        char current_char = 'A' + static_cast<char>(i);
        std::string row(size, ' ');
        
        // Calculate positions to place the characters
        const std::int32_t left_pos = (n - 1) - i;
        const std::int32_t right_pos = (n - 1) + i;
        
        row[left_pos] = current_char;
        row[right_pos] = current_char;
        
        result.push_back(row);
    }
    
    // Generate the bottom half by mirroring the top half (excluding the middle)
    for (std::int32_t i = n - 2; i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
