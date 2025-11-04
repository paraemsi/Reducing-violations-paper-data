#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return std::vector<std::string>{"A"};
    }
    
    // Define a type alias to avoid using standard integer types directly
    using index_t = std::int32_t;
    
    // Calculate the number of rows
    const index_t n = static_cast<index_t>(letter - 'A' + 1);
    const index_t num_rows = (2 * n) - 1;
    std::vector<std::string> result;
    
    // Build the top half including the middle
    for (index_t i = 0; i < n; i++) {
        std::string row(static_cast<size_t>(num_rows), ' ');
        const char current_char = static_cast<char>('A' + i);
        
        // Set the two characters in the row
        const index_t left_pos = (n - 1) - i;
        const index_t right_pos = (num_rows - 1) - left_pos;
        row[static_cast<size_t>(left_pos)] = current_char;
        row[static_cast<size_t>(right_pos)] = current_char;
        
        result.push_back(row);
    }
    
    // Build the bottom half by mirroring the top (excluding the middle)
    for (index_t i = (n - 2); i >= 0; i--) {
        result.push_back(result[static_cast<size_t>(i)]);
    }
    
    return result;
}

}  // namespace diamond
