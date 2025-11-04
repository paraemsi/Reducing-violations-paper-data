#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    // Handle 'A' case directly
    if (letter == 'A') {
        return std::vector<std::string>{"A"};
    }
    
    // Calculate the number of steps from 'A' to the input letter
    const int32_t n = static_cast<int32_t>(letter - 'A');
    std::vector<std::string> result;
    
    // Generate top half including the middle
    for (int32_t i = 0; i <= n; i++) {
        const char current_char = static_cast<char>('A' + i);
        const int32_t outer_spaces = n - i;
        const int32_t inner_spaces = (2 * i) - 1;
        
        // Build the row
        std::string row;
        // Add leading spaces
        row.append(outer_spaces, ' ');
        // Add the first character
        row += current_char;
        if (i > 0) {
            // Add inner spaces and the second character
            row.append(inner_spaces, ' ');
            row += current_char;
        }
        // Add trailing spaces
        row.append(outer_spaces, ' ');
        result.push_back(row);
    }
    
    // Generate bottom half by mirroring the top (excluding the middle)
    for (int32_t i = (n - 1); i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
