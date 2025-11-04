#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> result;
    
    if (letter == 'A') {
        result.push_back("A");
        return result;
    }
    
    // Number of different letters from 'A' to the input letter
    const std::int32_t n = static_cast<std::int32_t>(letter - 'A');
    // Number of rows is always 2*n + 1
    const std::int32_t num_rows = (2 * n) + 1;
    
    for (std::int32_t i = 0; i < num_rows; i++) {
        // Determine the current letter for this row
        // The index in the alphabet
        std::int32_t letter_idx;
        if (i <= n) {
            letter_idx = i;
        } else {
            letter_idx = num_rows - i - 1;
        }
        char current_letter = 'A' + static_cast<char>(letter_idx);
        
        // Calculate number of outer spaces
        const std::int32_t outer_spaces = n - letter_idx;
        // Calculate number of inner spaces (only if not 'A')
        std::int32_t inner_spaces = 0;
        if (letter_idx > 0) {
            inner_spaces = (2 * letter_idx) - 1;
        }
        
        // Build the row
        std::string row;
        // Add leading spaces
        row.append(static_cast<size_t>(outer_spaces), ' ');
        // Add first character
        row += current_letter;
        // Add inner spaces and second character if necessary
        if (letter_idx > 0) {
            row.append(static_cast<size_t>(inner_spaces), ' ');
            row += current_letter;
        }
        // Add trailing spaces
        row.append(static_cast<size_t>(outer_spaces), ' ');
        
        result.push_back(row);
    }
    
    return result;
}

}  // namespace diamond
