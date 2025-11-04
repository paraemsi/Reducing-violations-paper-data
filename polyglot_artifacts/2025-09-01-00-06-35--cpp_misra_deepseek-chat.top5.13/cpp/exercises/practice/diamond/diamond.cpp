#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> result;
    
    // Handle 'A' case directly
    if (letter == 'A') {
        result.push_back("A");
        return result;
    }
    
    // Define the alphabet
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // Find the index of the input letter
    std::int32_t target_index = 0;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(alphabet.size()); i++) {
        if (alphabet[i] == letter) {
            target_index = i;
            break;
        }
    }
    
    // Number of rows is always 2 * target_index + 1
    const std::int32_t num_rows = (2 * target_index) + 1;
    result.resize(num_rows);
    
    // Generate each row
    for (std::int32_t i = 0; i < num_rows; i++) {
        // Determine which character to use for this row
        std::int32_t char_index;
        if (i <= target_index) {
            char_index = i;
        } else {
            char_index = (2 * target_index) - i;
        }
        // Get the current character from the alphabet
        char current_char = alphabet[static_cast<std::size_t>(char_index)];
        
        // Create a string full of spaces
        std::string row(static_cast<std::size_t>(num_rows), ' ');
        
        // Calculate positions
        const std::int32_t left_pos = target_index - char_index;
        const std::int32_t right_pos = target_index + char_index;
        
        // Set characters at the appropriate positions
        row[static_cast<std::size_t>(left_pos)] = current_char;
        row[static_cast<std::size_t>(right_pos)] = current_char;
        
        result[static_cast<std::size_t>(i)] = row;
    }
    
    return result;
}

}  // namespace diamond
