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
    
    // Calculate the number of rows using uint32_t to follow the rules
    const std::uint32_t diff = static_cast<std::uint32_t>(letter - 'A');
    const std::uint32_t n = (2 * diff) + 1;
    
    // Generate each row
    for (std::uint32_t i = 0; i < n; i++) {
        // Determine which character to use for this row
        // The diamond is symmetric around the middle row
        std::uint32_t char_index;
        if (i <= (n / 2)) {
            char_index = i;
        } else {
            char_index = n - 1 - i;
        }
        const char current_char = 'A' + static_cast<char>(char_index);
        
        // Calculate leading spaces
        const std::uint32_t leading_spaces = (n / 2) - char_index;
        
        // Build the row
        std::string row;
        // Add leading spaces
        row.append(leading_spaces, ' ');
        
        // Add first character
        row += current_char;
        
        // Add middle spaces if not 'A'
        if (current_char != 'A') {
            const std::uint32_t middle_spaces = (2 * char_index) - 1;
            row.append(middle_spaces, ' ');
            // Add second character
            row += current_char;
        }
        
        // Add trailing spaces
        row.append(leading_spaces, ' ');
        diamond.push_back(row);
    }
    
    return diamond;
}

}  // namespace diamond
