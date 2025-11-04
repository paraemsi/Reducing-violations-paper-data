#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    // Find the index of the letter in the alphabet
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int32_t n = 0;
    for (int32_t i = 0; i < static_cast<int32_t>(alphabet.size()); i++) {
        if (alphabet[i] == letter) {
            n = i;
            break;
        }
    }
    
    std::vector<std::string> diamond_rows;
    
    // Generate top part up to the middle
    for (int32_t i = 0; i <= n; i++) {
        std::string row;
        
        // Add leading spaces
        int32_t leading_spaces = n - i;
        row.append(leading_spaces, ' ');
        
        // Add the current character
        char current_char = alphabet[i];
        row += current_char;
        
        // Add middle spaces and second character if not 'A'
        if (current_char != 'A') {
            int32_t middle_spaces = 2 * i - 1;
            row.append(middle_spaces, ' ');
            row += current_char;
        }
        
        // Add trailing spaces
        row.append(leading_spaces, ' ');
        diamond_rows.push_back(row);
    }
    
    // Generate bottom part by mirroring the top part (excluding the middle)
    for (int32_t i = n - 1; i >= 0; i--) {
        diamond_rows.push_back(diamond_rows[i]);
    }
    
    return diamond_rows;
}

}  // namespace diamond
