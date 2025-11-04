#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> result;
    
    // Handle 'A' case directly
    if (letter == 'A') {
        result.push_back("A");
        return result;
    }
    
    // Convert to integer indices to avoid character arithmetic
    const std::int32_t letter_index = static_cast<std::int32_t>(letter) - static_cast<std::int32_t>('A');
    const std::int32_t size = 2 * letter_index + 1;
    
    // Generate each row
    for (std::int32_t i = 0; i <= letter_index; i++) {
        std::string row(size, ' ');
        const std::int32_t current_char_int = static_cast<std::int32_t>('A') + i;
        const char current_char = static_cast<char>(current_char_int);
        
        // Calculate positions
        const std::int32_t left_pos = letter_index - i;
        const std::int32_t right_pos = letter_index + i;
        row[left_pos] = current_char;
        row[right_pos] = current_char;
        
        result.push_back(row);
    }
    
    // Add the bottom half by mirroring (excluding the middle row)
    for (std::int32_t i = result.size() - 2; i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
