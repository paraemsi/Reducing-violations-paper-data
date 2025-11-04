#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    // Determine the size of the diamond
    const std::int32_t n = letter - 'A' + 1;
    const std::int32_t size = 2 * n - 1;
    std::vector<std::string> diamond;
    
    // Build the top half including the middle
    for (std::int32_t i = 0; i < n; i++) {
        std::string row(size, ' ');
        // To avoid character arithmetic, use a lookup
        const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const char current_char = letters[i];
        
        // Set leading and trailing spaces
        const std::int32_t left = n - 1 - i;
        const std::int32_t right = size - 1 - left;
        
        row[left] = current_char;
        if (current_char != 'A') {
            row[right] = current_char;
        }
        
        diamond.push_back(row);
    }
    
    // Build the bottom half by mirroring the top (excluding the middle)
    for (std::int32_t i = n - 2; i >= 0; i--) {
        diamond.push_back(diamond[i]);
    }
    
    return diamond;
}

}  // namespace diamond
