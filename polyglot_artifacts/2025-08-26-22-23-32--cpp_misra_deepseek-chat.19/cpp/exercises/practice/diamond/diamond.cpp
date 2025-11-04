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
    
    // Calculate the difference from 'A'
    const std::int32_t diff = static_cast<std::int32_t>(letter - 'A');
    
    // Generate top half including the middle
    for (std::int32_t i = 0; i <= diff; i++) {
        char current_char = 'A' + static_cast<char>(i);
        std::int32_t outer_spaces = diff - i;
        std::string row;
        
        // Add leading spaces
        row.append(static_cast<std::size_t>(outer_spaces), ' ');
        
        // Add first character
        row += current_char;
        
        if (current_char != 'A') {
            std::int32_t inner_spaces = 2 * i - 1;
            row.append(static_cast<std::size_t>(inner_spaces), ' ');
            row += current_char;
        }
        
        // Add trailing spaces
        row.append(static_cast<std::size_t>(outer_spaces), ' ');
        diamond.push_back(row);
    }
    
    // Generate bottom half (mirror of the top without the middle)
    for (std::int32_t i = diff - 1; i >= 0; i--) {
        diamond.push_back(diamond[static_cast<std::size_t>(i)]);
    }
    
    return diamond;
}

}  // namespace diamond
