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
    
    // Number of rows
    const int32_t n = 2 * (letter - 'A') + 1;
    const int32_t mid_point = n / 2;
    
    // Generate each row
    for (int32_t i = 0; i < n; i++) {
        // Determine the current character
        const int32_t distance_from_mid = (i <= mid_point) ? (mid_point - i) : (i - mid_point);
        const char current_char = letter - distance_from_mid;
        
        // Calculate number of leading and trailing spaces
        const int32_t leading_spaces = distance_from_mid;
        
        // Calculate number of middle spaces
        const int32_t middle_spaces = (current_char == 'A') ? 0 : (2 * (current_char - 'A') - 1);
        
        // Build the row
        std::string row;
        
        // Add leading spaces
        row.append(leading_spaces, ' ');
        
        // Add first character
        row += current_char;
        
        // Add middle spaces if necessary
        if (middle_spaces > 0) {
            row.append(middle_spaces, ' ');
            // Add second character
            row += current_char;
        }
        
        // Add trailing spaces (same as leading spaces)
        row.append(leading_spaces, ' ');
        
        result.push_back(row);
    }
    
    return result;
}

}  // namespace diamond
