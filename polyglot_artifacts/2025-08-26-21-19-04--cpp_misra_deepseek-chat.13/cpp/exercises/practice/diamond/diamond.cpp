#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    // Handle 'A' case
    if (letter == 'A') {
        return std::vector<std::string>{"A"};
    }
    
    // Calculate the number of rows which is always odd
    const std::int32_t diff = static_cast<std::int32_t>(letter - 'A');
    const std::int32_t n = (diff * 2) + 1;
    const std::int32_t half_point = diff;
    std::vector<std::string> result;
    
    // Generate each row
    for (std::int32_t i = 0; i < n; i++) {
        // Determine which character to print
        const std::int32_t distance_from_center = (i <= half_point) ? (half_point - i) : (i - half_point);
        const char current_char = static_cast<char>(letter - distance_from_center);
        
        // Create a row full of spaces
        std::string row(static_cast<std::size_t>(n), ' ');
        
        // Set the appropriate characters
        const std::int32_t left_pos = half_point - distance_from_center;
        const std::int32_t right_pos = half_point + distance_from_center;
        
        row[static_cast<std::size_t>(left_pos)] = current_char;
        row[static_cast<std::size_t>(right_pos)] = current_char;
        
        result.push_back(row);
    }
    
    return result;
}

}  // namespace diamond
