#include "diamond.h"
#include <vector>
#include <string>
#include <cstddef>

namespace diamond {

std::vector<std::string> rows(char letter) {
    // Create a string with all uppercase letters
    const std::string all_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // Find the index of the target letter
    std::size_t target_index = 0;
    while (true) {
        if (all_letters[target_index] == letter) {
            break;
        }
        target_index++;
    }
    
    // Handle 'A' case
    if (letter == 'A') { 
        return {"A"};
    }
    
    // Generate all letters up to the target letter
    std::vector<char> letters;
    for (std::size_t i = 0; i <= target_index; i++) {
        letters.push_back(all_letters[i]);
    }
    
    // The number of rows is always odd: 2*n - 1
    std::vector<std::string> result;
    const std::size_t size = (2U * letters.size()) - 1U;
    
    // Generate each row
    for (std::size_t i = 0; i < size; i++) {
        std::string row(size, ' ');
        
        // Determine which character to place
        std::size_t index;
        if (i < letters.size()) { 
            index = i;
        } else { 
            index = size - i - 1U;
        }
        char current_char = letters[index];
        
        // Determine positions to place the characters
        const std::size_t middle = (size - 1U) / 2U;
        const std::size_t left_pos = middle - index;
        const std::size_t right_pos = middle + index;
        
        row[left_pos] = current_char;
        row[right_pos] = current_char;
        
        result.push_back(row);
    }
    
    return result;
}

}  // namespace diamond
