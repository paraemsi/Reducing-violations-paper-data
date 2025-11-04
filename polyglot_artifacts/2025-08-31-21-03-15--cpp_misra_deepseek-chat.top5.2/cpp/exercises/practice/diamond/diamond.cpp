#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

namespace diamond {

std::vector<std::string> rows(char letter) {
    // Create a string of all uppercase letters
    const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // Find the index of the input letter
    const std::size_t index = letters.find(letter);
    
    if (index == std::string::npos) {
        // Handle invalid input (though the problem probably assumes valid input)
        return {};
    }
    
    // For 'A' case
    if (letter == 'A') {
        return {"A"};
    }
    
    // Convert index to int32_t to avoid signed/unsigned issues
    const int32_t n = static_cast<int32_t>(index);
    const int32_t size = 2 * n + 1;
    std::vector<std::string> result;
    
    // Generate top half including the middle
    for (int32_t i = 0; i <= n; i++) {
        std::string row(size, ' ');
        // Get the current letter using the letters string
        const char current_char = letters[static_cast<std::size_t>(i)];
        
        // Calculate positions
        const int32_t left_pos = n - i;
        const int32_t right_pos = n + i;
        row[left_pos] = current_char;
        row[right_pos] = current_char;
        
        result.push_back(row);
    }
    
    // Generate bottom half by mirroring the top (excluding the middle)
    for (int32_t i = n - 1; i >= 0; i--) {
        result.push_back(result[static_cast<std::size_t>(i)]);
    }
    
    return result;
}

}  // namespace diamond
