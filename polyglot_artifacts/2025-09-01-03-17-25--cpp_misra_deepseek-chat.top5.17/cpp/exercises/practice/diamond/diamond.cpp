#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    // All possible letters in order
    const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // Find the index of the target letter
    int32_t index = 0;
    for (int32_t i = 0; i < static_cast<int32_t>(letters.size()); i++) {
        if (letters[i] == letter) {
            index = i;
            break;
        }
    }
    
    // The number of rows is 2*index + 1
    int32_t num_rows = 2 * index + 1;
    std::vector<std::string> result;
    result.reserve(num_rows);
    
    // Generate each row
    for (int32_t i = 0; i < num_rows; i++) {
        // Determine which letter to use for this row
        int32_t current_index;
        if (i <= index) {
            current_index = i;
        } else {
            current_index = num_rows - i - 1;
        }
        char current_char = letters[current_index];
        
        // Calculate number of spaces
        int32_t outer_spaces = index - current_index;
        int32_t inner_spaces = 2 * current_index - 1;
        
        // Build the row string
        if (current_index == 0) {
            std::string row = std::string(outer_spaces, ' ') + std::string(1, current_char) + 
                              std::string(outer_spaces, ' ');
            result.push_back(row);
        } else {
            std::string row = std::string(outer_spaces, ' ') + std::string(1, current_char) + 
                              std::string(inner_spaces, ' ') + std::string(1, current_char) + 
                              std::string(outer_spaces, ' ');
            result.push_back(row);
        }
    }
    
    return result;
}

}  // namespace diamond
