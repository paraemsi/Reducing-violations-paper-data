#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return std::vector<std::string>{"A"};
    }
    
    // Use a type alias for the integer type
    using index_t = std::int32_t;
    
    // Calculate the number of distinct letters from 'A' to the input letter
    const index_t n = static_cast<index_t>(letter - 'A') + 1;
    const index_t total_rows = (2 * n) - 1;
    std::vector<std::string> result;
    
    // Generate the top half including the middle
    for (index_t i = 0; i < n; i++) {
        std::string row(total_rows, ' ');
        const char current_char = static_cast<char>('A' + i);
        
        // Calculate positions
        const index_t left_pos = n - 1 - i;
        const index_t right_pos = total_rows - 1 - left_pos;
        
        row[left_pos] = current_char;
        row[right_pos] = current_char;
        
        result.push_back(row);
    }
    
    // Generate the bottom half by mirroring the top (excluding the middle)
    for (index_t i = static_cast<index_t>(n - 2); i >= 0; i--) {
        result.push_back(result[static_cast<size_t>(i)]);
    }
    
    return result;
}

}  // namespace diamond
