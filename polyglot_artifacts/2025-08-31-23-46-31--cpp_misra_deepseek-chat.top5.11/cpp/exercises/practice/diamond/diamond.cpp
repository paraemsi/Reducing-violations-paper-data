#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    // Define all possible letters to avoid character arithmetic
    const std::string all_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // Find the index of the input letter
    int32_t target_index = 0;
    for (size_t i = 0; i < all_letters.size(); i++) {
        if (all_letters[i] == letter) {
            target_index = static_cast<int32_t>(i);
            break;
        }
    }
    
    const int32_t n = target_index + 1;
    const int32_t num_rows = 2 * n - 1;
    std::vector<std::string> result;
    
    // Build the top half including the middle
    for (int32_t i = 0; i < n; i++) {
        std::string row(num_rows, ' ');
        const char current_char = all_letters[static_cast<size_t>(i)];
        
        // Set the appropriate positions
        const int32_t left_pos = (n - 1) - i;
        const int32_t right_pos = (num_rows - 1) - left_pos;
        row[static_cast<size_t>(left_pos)] = current_char;
        row[static_cast<size_t>(right_pos)] = current_char;
        
        result.push_back(row);
    }
    
    // Build the bottom half by mirroring the top (excluding the middle)
    for (int32_t i = static_cast<int32_t>(result.size()) - 2; i >= 0; i--) {
        result.push_back(result[static_cast<size_t>(i)]);
    }
    
    return result;
}

}  // namespace diamond
