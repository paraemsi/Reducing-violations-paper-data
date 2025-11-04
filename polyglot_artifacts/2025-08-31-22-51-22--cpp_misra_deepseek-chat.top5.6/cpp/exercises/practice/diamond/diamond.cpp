#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> diamond;
    
    // Handle 'A' case
    if (letter == 'A') {
        diamond.push_back("A");
        return diamond;
    }
    
    // Determine the index of the letter
    // To avoid character arithmetic, we'll use a lookup approach
    const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::int32_t index = 0;
    // Find the index of the input letter
    for (; index < 26; index++) {
        if (letters[index] == letter) {
            break;
        }
    }
    // Ensure we found the letter (index will be less than 26)
    const std::int32_t n = index + 1;
    const std::int32_t num_rows = (2 * n) - 1;
    
    // Pre-allocate the result
    diamond.reserve(static_cast<std::size_t>(num_rows));
    
    // Generate each row
    for (std::int32_t i = 0; i < n; i++) {
        std::string row(static_cast<std::size_t>(num_rows), ' ');
        // Get the current letter
        const char current_letter = letters[i];
        
        // Calculate positions
        const std::int32_t left_pos = (n - 1) - i;
        const std::int32_t right_pos = (num_rows - n) + i;
        
        // Set the letters at the appropriate positions
        row[static_cast<std::size_t>(left_pos)] = current_letter;
        row[static_cast<std::size_t>(right_pos)] = current_letter;
        
        diamond.push_back(row);
    }
    
    // Add the bottom half by mirroring the top (excluding the middle)
    for (std::int32_t i = (n - 2); i >= 0; i--) {
        diamond.push_back(diamond[static_cast<std::size_t>(i)]);
    }
    
    return diamond;
}

}  // namespace diamond
