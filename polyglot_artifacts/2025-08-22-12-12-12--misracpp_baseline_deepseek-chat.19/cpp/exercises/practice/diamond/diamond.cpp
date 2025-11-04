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
    // Generate each row
    for (int i = 0; i <= n; i++) {
        char current_char = 'A' + i;
        int outer_spaces = n - i;
        std::string row;
        // Add leading spaces
        row.append(outer_spaces, ' ');
        // Add first character
        row += current_char;
        if (current_char != 'A') {
            int inner_spaces = 2 * i - 1;
            row.append(inner_spaces, ' ');
            // Add second character
            row += current_char;
        }
        // Add trailing spaces
        row.append(outer_spaces, ' ');
        result.push_back(row);
    }
    
    // Add the bottom half by mirroring the top (excluding the middle)
    for (int i = result.size() - 2; i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
