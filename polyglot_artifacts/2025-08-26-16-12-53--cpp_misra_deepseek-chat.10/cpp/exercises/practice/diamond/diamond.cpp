#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>
#include <cmath>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    const int32_t n = letter - 'A';
    const int32_t size = 2 * n + 1;
    std::vector<std::string> diamond;
    
    for (int32_t i = 0; i < size; i++) {
        // Calculate distance from the middle row
        const int32_t distance_from_middle = std::abs(i - n);
        const char current_char = 'A' + n - distance_from_middle;
        
        // Build the row
        std::string row;
        
        // Add leading spaces
        row.append(static_cast<size_t>(distance_from_middle), ' ');
        
        // Add first character
        row += current_char;
        
        // Add middle spaces and second character if not 'A'
        if (current_char != 'A') {
            const int32_t middle_spaces = size - 2 * distance_from_middle - 2;
            row.append(static_cast<size_t>(middle_spaces), ' ');
            row += current_char;
        }
        
        // Add trailing spaces
        row.append(static_cast<size_t>(distance_from_middle), ' ');
        
        diamond.push_back(row);
    }
    
    return diamond;
}

}  // namespace diamond
