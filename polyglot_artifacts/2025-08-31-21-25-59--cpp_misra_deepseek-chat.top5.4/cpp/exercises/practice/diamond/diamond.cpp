#include "diamond.h"
#include <string>
#include <vector>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    // Build a list of all uppercase letters
    const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // Find the index of the target letter using only equality comparisons
    std::int32_t target_index = 0;
    for (std::int32_t i = 0; i < 26; i++) {
        if (letters[i] == letter) {
            target_index = i;
            break;
        }
    }
    
    // Calculate size
    std::int32_t size = ((2 * target_index) + 1);
    std::vector<std::string> diamond;
    
    // Generate each row
    for (std::int32_t i = 0; i < size; i++) {
        std::string row(size, ' ');
        
        // Determine distance from center
        std::int32_t distance_from_center;
        if (i <= target_index) {
            distance_from_center = i;
        } else {
            distance_from_center = ((size - 1) - i);
        }
        
        // Get the corresponding letter
        char current_letter = letters[distance_from_center];
        
        // Calculate positions
        std::int32_t left_pos = (target_index - distance_from_center);
        std::int32_t right_pos = (target_index + distance_from_center);
        
        // Place the letters
        row[left_pos] = current_letter;
        row[right_pos] = current_letter;
        
        diamond.push_back(row);
    }
    
    return diamond;
}

}  // namespace diamond
