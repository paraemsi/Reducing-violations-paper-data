#include "diamond.h"
#include <vector>
#include <string>
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> result;
    
    // Generate all letters from 'A' to the input letter
    std::string letters;
    for (char c = 'A'; c <= letter; c++) {
        letters += c;
    }
    
    const int32_t n = static_cast<int32_t>(letters.size());
    
    // Generate each row
    for (int32_t i = 0; i < n; i++) {
        const int32_t outer_spaces = n - 1 - i;
        std::string row;
        
        // Add leading spaces
        row.append(outer_spaces, ' ');
        
        // Add the current letter
        row += letters[i];
        
        // Add inner spaces if not the first row
        if (i > 0) {
            const int32_t inner_spaces = 2 * i - 1;
            row.append(inner_spaces, ' ');
            // Add the second instance of the letter
            row += letters[i];
        }
        
        // Add trailing spaces
        row.append(outer_spaces, ' ');
        result.push_back(row);
    }
    
    // Add the mirrored bottom half (excluding the middle)
    for (int32_t i = n - 2; i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
