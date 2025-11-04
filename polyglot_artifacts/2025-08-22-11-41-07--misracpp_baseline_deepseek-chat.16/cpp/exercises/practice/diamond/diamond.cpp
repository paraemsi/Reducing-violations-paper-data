#include "diamond.h"
#include <vector>
#include <string>
#include <algorithm>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    int n = letter - 'A';
    std::vector<std::string> result;
    
    // Generate top half
    for (int i = 0; i <= n; i++) {
        char current_char = 'A' + i;
        int padding = n - i;
        std::string row;
        // Add leading spaces
        row.append(padding, ' ');
        // Add first character
        row += current_char;
        if (current_char != 'A') {
            int middle_spaces = 2 * i - 1;
            row.append(middle_spaces, ' ');
            row += current_char;
        }
        // Add trailing spaces
        row.append(padding, ' ');
        result.push_back(row);
    }
    
    // Generate bottom half by reversing the top half (excluding the middle)
    for (int i = n - 1; i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
