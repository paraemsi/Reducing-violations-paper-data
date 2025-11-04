#include "diamond.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // Find the index of the letter
    auto it = std::find(alphabet.begin(), alphabet.end(), letter);
    std::int32_t index = static_cast<std::int32_t>(it - alphabet.begin());
    
    std::int32_t size = (2 * index) + 1;
    std::vector<std::string> result;
    
    // Generate each row
    for (std::int32_t i = 0; i <= index; i++) {
        std::string row(size, ' ');
        // The current letter to place
        char current_letter = alphabet[static_cast<std::size_t>(i)];
        
        // Calculate positions to place the letters
        std::int32_t left_pos = index - i;
        std::int32_t right_pos = index + i;
        
        row[static_cast<std::size_t>(left_pos)] = current_letter;
        row[static_cast<std::size_t>(right_pos)] = current_letter;
        
        result.push_back(row);
    }
    
    // Add the bottom half by mirroring the top (excluding the middle)
    for (std::int32_t i = index - 1; i >= 0; i--) {
        result.push_back(result[static_cast<std::size_t>(i)]);
    }
    
    return result;
}

}  // namespace diamond
