#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>
#include <cstddef>

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> result;
    
    if (letter == 'A') {
        result.push_back("A");
        return result;
    }
    
    const std::int32_t n = static_cast<std::int32_t>(letter - 'A');
    const std::int32_t size = (2 * n) + 1;
    
    // Build top half up to and including the middle
    for (std::int32_t i = 0; i <= n; i++) {
        const char current_char = static_cast<char>('A' + i);
        const std::int32_t leading_spaces = n - i;
        std::string row;
        
        // Add leading spaces
        row.append(static_cast<std::size_t>(leading_spaces), ' ');
        
        // Add the first character
        row += current_char;
        
        if (current_char != 'A') {
            // Add middle spaces
            const std::int32_t middle_spaces = (2 * i) - 1;
            row.append(static_cast<std::size_t>(middle_spaces), ' ');
            // Add the second character
            row += current_char;
        }
        
        // Add trailing spaces to match leading spaces
        row.append(static_cast<std::size_t>(leading_spaces), ' ');
        
        result.push_back(row);
    }
    
    // Build bottom half by mirroring the top (excluding the middle)
    for (std::int32_t i = (n - 1); i >= 0; i--) {
        result.push_back(result[static_cast<std::size_t>(i)]);
    }
    
    return result;
}

}  // namespace diamond
