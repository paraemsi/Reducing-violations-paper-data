#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

// Define a type alias to avoid using standard integer types directly
using index_t = std::int32_t;

std::vector<std::string> rows(char letter) {
    // Handle 'A' case
    if (letter == 'A') {
        return std::vector<std::string>(1, "A");
    }
    
    // Calculate the number of steps from 'A'
    const index_t n = static_cast<index_t>(letter - 'A');
    // Number of rows is always 2n + 1
    const index_t num_rows = (2 * n) + 1;
    std::vector<std::string> result;
    result.reserve(static_cast<size_t>(num_rows));
    
    // Generate each row
    for (index_t i = 0; i <= n; i++) {
        // The current character to use
        const char current_char = static_cast<char>('A' + i);
        // Number of leading/trailing spaces
        const index_t outer_spaces = n - i;
        // Number of inner spaces between characters (0 for 'A')
        const index_t inner_spaces = (2 * i) - 1;
        
        // Build the row string
        std::string row;
        // Add leading spaces
        row.append(static_cast<size_t>(outer_spaces), ' ');
        // Add first character
        row += current_char;
        if (i > 0) {
            // Add inner spaces and second character
            row.append(static_cast<size_t>(inner_spaces), ' ');
            row += current_char;
        }
        // Add trailing spaces
        row.append(static_cast<size_t>(outer_spaces), ' ');
        
        result.push_back(row);
    }
    
    // Add the mirrored bottom half (excluding the middle row)
    for (index_t i = (n - 1); i >= 0; i--) {
        result.push_back(result[static_cast<size_t>(i)]);
    }
    
    return result;
}

}  // namespace diamond
