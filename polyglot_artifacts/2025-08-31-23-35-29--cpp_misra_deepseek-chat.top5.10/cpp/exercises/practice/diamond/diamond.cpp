#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    // Calculate the size of the diamond
    // Since we can't do arithmetic with characters directly, we'll use their integer values
    // But according to MISRA, we can't use the numerical value of a character
    // So we need to find another approach
    // Let's use a lookup or index-based approach
    
    // Since the letters are in order, we can find the index of the letter
    // 'A' is at index 0, 'B' at 1, etc.
    // To avoid character arithmetic, we'll use a string to find the index
    const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::int32_t index = 0;
    for (std::int32_t i = 0; (i < static_cast<std::int32_t>(letters.size())); i++) {
        if (letters[i] == letter) {
            index = i;
            break;
        }
    }
    
    std::int32_t size = (2 * index) + 1;
    std::vector<std::string> diamond(size);
    
    // Generate top half including the middle
    for (std::int32_t i = 0; (i <= index); i++) {
        std::string line(size, ' ');
        // Set the appropriate characters
        // The current letter to use
        char current_letter = letters[i];
        
        // Positions to place the letters
        std::int32_t left_pos = (index - i);
        std::int32_t right_pos = (index + i);
        
        line[left_pos] = current_letter;
        line[right_pos] = current_letter;
        
        diamond[i] = line;
        // The bottom half will be symmetric to the top half
    }
    
    // Generate bottom half by mirroring the top half (excluding the middle)
    for (std::int32_t i = (index + 1); (i < size); i++) {
        diamond[i] = diamond[(size - 1) - i];
    }
    
    return diamond;
}

}  // namespace diamond
