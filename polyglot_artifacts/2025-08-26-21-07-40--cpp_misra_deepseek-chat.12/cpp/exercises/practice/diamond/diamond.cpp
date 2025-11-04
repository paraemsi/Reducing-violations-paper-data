#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> diamond;
    
    // Handle 'A' case directly
    if (letter == 'A') {
        diamond.push_back("A");
        return diamond;
    }
    
    // Calculate the number of rows
    const int32_t n = (static_cast<int32_t>(letter) - static_cast<int32_t>('A')) * 2 + 1;
    const int32_t half_size = (n / 2);
    
    // Generate each row
    for (int32_t i = 0; i < n; i++) {
        // Determine the current character
        int32_t distance_from_center;
        if (i <= half_size) {
            distance_from_center = i;
        } else {
            distance_from_center = n - 1 - i;
        }
        char current_char = 'A' + distance_from_center;
        
        // Calculate leading and trailing spaces
        int32_t outer_spaces = half_size - distance_from_center;
        
        // Build the line
        std::string line;
        // Add leading spaces
        line.append(outer_spaces, ' ');
        
        // Add first character
        line += current_char;
        
        // Add inner spaces if not 'A'
        if (current_char != 'A') {
            int32_t inner_spaces = 2 * distance_from_center - 1;
            line.append(inner_spaces, ' ');
            // Add second character
            line += current_char;
        }
        
        // Add trailing spaces
        line.append(outer_spaces, ' ');
        
        diamond.push_back(line);
    }
    
    return diamond;
}

}  // namespace diamond
