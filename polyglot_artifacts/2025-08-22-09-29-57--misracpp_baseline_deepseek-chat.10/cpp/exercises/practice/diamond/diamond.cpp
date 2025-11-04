#include "diamond.h"
#include <vector>
#include <string>
#include <algorithm>

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> result;
    if (letter == 'A') {
        result.push_back("A");
        return result;
    }
    
    int n = letter - 'A';
    
    // Generate top part up to and including the middle
    for (int i = 0; i <= n; i++) {
        char current_char = 'A' + i;
        int outer_spaces = n - i;
        int inner_spaces = 2 * i - 1;
        
        std::string row;
        // Add leading spaces
        row.append(outer_spaces, ' ');
        // Add the first character
        row += current_char;
        if (i > 0) {
            // Add inner spaces and the second character
            row.append(inner_spaces, ' ');
            row += current_char;
        }
        // Add trailing spaces
        row.append(outer_spaces, ' ');
        result.push_back(row);
    }
    
    // Generate bottom part by mirroring the top part (excluding the middle)
    for (int i = n - 1; i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
