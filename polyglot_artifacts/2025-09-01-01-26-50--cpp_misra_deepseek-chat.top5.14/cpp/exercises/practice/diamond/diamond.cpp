#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> result;
    
    // Handle 'A' case
    if (letter == 'A') {
        result.push_back("A");
        return result;
    }
    
    // Create a list of letters up to the input letter
    const char all_letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // Find the index of the input letter
    std::int32_t max_index = 0;
    while (true) {
        if (all_letters[max_index] == letter) {
            break;
        }
        max_index++;
    }
    
    // Number of rows is always odd: 2 * max_index + 1
    std::int32_t num_rows = (2 * max_index) + 1;
    result.reserve(static_cast<std::size_t>(num_rows));
    
    // Generate each row
    for (std::int32_t i = 0; i < num_rows; i++) {
        // Create a string of spaces with length num_rows
        std::string row(static_cast<std::size_t>(num_rows), ' ');
        
        // Determine which letter to place in this row
        std::int32_t letter_index;
        if (i <= max_index) {
            letter_index = i;
        } else {
            letter_index = (num_rows - i) - 1;
        }
        char current_letter = all_letters[letter_index];
        
        // Calculate positions to place the letters
        std::int32_t left_pos = max_index - letter_index;
        std::int32_t right_pos = max_index + letter_index;
        
        // Place the letters
        row[static_cast<std::size_t>(left_pos)] = current_letter;
        row[static_cast<std::size_t>(right_pos)] = current_letter;
        
        result.push_back(row);
    }
    
    return result;
}

}  // namespace diamond
