#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    // Find n using allowed operations
    const std::string all_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int32_t n = 0;
    while (true) {
        if (all_letters[n] == letter) {
            { break; }
        }
        n++;
    }
    
    const int32_t size = (2 * n) + 1;
    std::vector<std::string> result;
    
    // Generate each row
    for (int32_t i = 0; i <= n; i++) {
        std::string row(size, ' ');
        // Get the current letter to place
        const char current_letter = all_letters[i];
        
        // Calculate positions
        const int32_t left_pos = n - i;
        const int32_t right_pos = n + i;
        row[left_pos] = current_letter;
        row[right_pos] = current_letter;
        
        result.push_back(row);
    }
    
    // Add the bottom half by mirroring the top (excluding the middle)
    for (int32_t i = n - 1; i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
