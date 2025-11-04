#include "diamond.h"
#include <vector>
#include <string>

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> diamond;
    if (letter == 'A') {
        diamond.push_back("A");
        return diamond;
    }
    
    int n = letter - 'A';
    
    // Generate top half including the middle
    for (int i = 0; i <= n; i++) {
        char current_char = 'A' + i;
        int outer_spaces = n - i;
        int inner_spaces = 2 * i - 1;
        
        std::string row;
        // Add leading spaces
        row.append(outer_spaces, ' ');
        // Add first character
        row += current_char;
        // Add inner spaces and second character if not 'A'
        if (i > 0) {
            row.append(inner_spaces, ' ');
            row += current_char;
        }
        // Add trailing spaces
        row.append(outer_spaces, ' ');
        diamond.push_back(row);
    }
    
    // Add the bottom half by mirroring the top (excluding the middle)
    for (int i = n - 1; i >= 0; i--) {
        diamond.push_back(diamond[i]);
    }
    
    return diamond;
}

}  // namespace diamond
