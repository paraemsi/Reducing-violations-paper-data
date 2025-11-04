#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> diamond;
    
    if (letter == 'A') {
        diamond.push_back("A");
        return diamond;
    }
    
    // Calculate the number of rows
    const int32_t n = static_cast<int32_t>(letter - 'A');
    const int32_t size = 2 * n + 1;
    
    // Generate each row
    for (int32_t i = 0; i < size; i++) {
        // Determine which character to use
        int32_t distance_from_center;
        if (i <= n) {
            distance_from_center = i;
        } else {
            distance_from_center = size - 1 - i;
        }
        char current_char = 'A' + distance_from_center;
        
        // Calculate leading and trailing spaces
        int32_t outer_spaces = n - distance_from_center;
        
        // Calculate inner spaces
        int32_t inner_spaces = 2 * distance_from_center - 1;
        
        // Build the row
        std::string row;
        // Add leading spaces
        row.append(outer_spaces, ' ');
        
        if (current_char == 'A') {
            row += 'A';
        } else {
            row += current_char;
            row.append(inner_spaces, ' ');
            row += current_char;
        }
        
        // Add trailing spaces
        row.append(outer_spaces, ' ');
        diamond.push_back(row);
    }
    
    return diamond;
}

}  // namespace diamond
