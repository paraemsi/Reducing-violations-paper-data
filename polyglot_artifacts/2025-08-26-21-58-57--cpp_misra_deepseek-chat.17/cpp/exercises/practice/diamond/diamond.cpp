#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    // Calculate the size of the diamond
    const std::int32_t n = static_cast<std::int32_t>(letter - 'A');
    const std::int32_t size = (2 * n) + 1;
    
    // Initialize all rows with spaces
    std::vector<std::string> result(size, std::string(size, ' '));
    
    // Fill the top half including the middle
    for (std::int32_t i = 0; i <= n; i++) {
        const char current_char = static_cast<char>('A' + i);
        const std::int32_t left_pos = n - i;
        const std::int32_t right_pos = n + i;
        
        // Top and bottom rows
        result[i][left_pos] = current_char;
        result[i][right_pos] = current_char;
        
        // Mirror to the bottom half
        result[size - 1 - i][left_pos] = current_char;
        result[size - 1 - i][right_pos] = current_char;
    }
    
    return result;
}

}  // namespace diamond
