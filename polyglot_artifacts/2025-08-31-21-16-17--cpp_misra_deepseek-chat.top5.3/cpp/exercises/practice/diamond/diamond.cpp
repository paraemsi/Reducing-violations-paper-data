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
    
    // Convert the input letter to its integer value
    const std::int32_t letter_val = std::char_traits<char>::to_int_type(letter);
    // Convert 'A' to its integer value
    const std::int32_t a_val = std::char_traits<char>::to_int_type('A');
    
    // Calculate the index
    const std::int32_t letter_index = (letter_val - a_val);
    const std::int32_t size = ((2 * letter_index) + 1);
    std::vector<std::string> result;
    
    // Build each row
    for (std::int32_t i = 0; i <= letter_index; i++) {
        std::string row(size, ' ');
        // Calculate the current character's integer value
        const std::int32_t current_char_val = (a_val + i);
        // Convert back to char using to_char_type
        const char current_char = std::char_traits<char>::to_char_type(current_char_val);
        
        // Calculate positions
        const std::int32_t left_pos = (letter_index - i);
        const std::int32_t right_pos = ((size - left_pos) - 1);
        
        // Set characters
        row[left_pos] = current_char;
        row[right_pos] = current_char;
        
        result.push_back(row);
    }
    
    // Add the bottom half by reversing the top half (excluding the middle)
    for (std::int32_t i = (static_cast<std::int32_t>(result.size()) - 2); i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
