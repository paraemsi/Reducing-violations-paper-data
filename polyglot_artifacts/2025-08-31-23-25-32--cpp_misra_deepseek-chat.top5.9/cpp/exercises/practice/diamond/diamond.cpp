#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    // First, handle the case where the letter is 'A'
    if (letter == 'A') {
        return {"A"};
    }
    
    // Generate all uppercase letters to find the index
    const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // Find the index of the input letter
    std::int32_t index = 0;
    for (std::int32_t i = 0; i < 26; i++) {
        if (letters[i] == letter) {
            index = i;
            break;
        }
    }
    
    std::vector<std::string> result;
    
    // Generate top half up to and including the middle
    for (std::int32_t i = 0; i <= index; i++) {
        std::string row;
        
        // Add leading spaces
        std::int32_t leading_spaces = index - i;
        row.append(static_cast<size_t>(leading_spaces), ' ');
        
        // Add the current character
        row += letters[i];
        
        // Add inner spaces if not the first row
        if (i > 0) {
            std::int32_t inner_spaces = 2 * i - 1;
            row.append(static_cast<size_t>(inner_spaces), ' ');
            // Add the second character
            row += letters[i];
        }
        
        // Add trailing spaces
        row.append(static_cast<size_t>(leading_spaces), ' ');
        
        result.push_back(row);
    }
    
    // Generate bottom half by mirroring the top (excluding the middle)
    for (std::int32_t i = static_cast<std::int32_t>(result.size()) - 2; i >= 0; i--) {
        result.push_back(result[static_cast<size_t>(i)]);
    }
    
    return result;
}

}  // namespace diamond
