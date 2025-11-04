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
    
    const int32_t diff = static_cast<int32_t>(letter - 'A');
    
    // Generate top half including the middle
    for (int32_t i = 0; i <= diff; i++) {
        const char current_char = static_cast<char>('A' + i);
        const int32_t outer_spaces = diff - i;
        std::string row;
        
        // Add leading spaces
        row.append(static_cast<size_t>(outer_spaces), ' ');
        
        // Add the first character
        row += current_char;
        
        // Add inner spaces and second character if not 'A'
        if (current_char == 'A') {
            // For 'A', no second character, just add trailing spaces
            row.append(static_cast<size_t>(outer_spaces), ' ');
        } else {
            const int32_t inner_spaces = (2 * i) - 1;
            row.append(static_cast<size_t>(inner_spaces), ' ');
            row += current_char;
            // Add trailing spaces
            row.append(static_cast<size_t>(outer_spaces), ' ');
        }
        
        diamond.push_back(row);
    }
    
    // Generate bottom half by mirroring the top (excluding the middle)
    for (int32_t i = diff - 1; i >= 0; i--) {
        diamond.push_back(diamond[static_cast<size_t>(i)]);
    }
    
    return diamond;
}

}  // namespace diamond
