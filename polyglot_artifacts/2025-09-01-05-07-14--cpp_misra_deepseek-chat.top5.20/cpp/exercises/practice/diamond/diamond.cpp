#include "diamond.h"
#include <string>
#include <vector>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // Find the index of the letter in the alphabet
    std::int32_t index = 0;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(alphabet.size()); i++) {
        if (alphabet[i] == letter) {
            index = i;
            break;
        }
    }
    
    // The number of rows is 2 * index + 1
    std::int32_t n = (2 * index) + 1;
    std::vector<std::string> result;
    
    for (std::int32_t i = 0; i < n; i++) {
        // Determine which character to place
        std::int32_t char_index = 0;
        if (i <= index) {
            char_index = i;
        } else {
            char_index = n - 1 - i;
        }
        char current_char = alphabet[static_cast<std::size_t>(char_index)];
        
        // Create a string of spaces
        std::string row(n, ' ');
        
        // Set the appropriate positions to the character
        std::int32_t left_pos = index - char_index;
        std::int32_t right_pos = index + char_index;
        row[static_cast<std::size_t>(left_pos)] = current_char;
        row[static_cast<std::size_t>(right_pos)] = current_char;
        
        result.push_back(row);
    }
    
    return result;
}

}  // namespace diamond
