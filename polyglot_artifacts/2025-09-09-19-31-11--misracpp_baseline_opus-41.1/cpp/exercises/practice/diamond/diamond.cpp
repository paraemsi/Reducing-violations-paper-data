#include "diamond.h"
#include <algorithm>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    // Calculate the size of the diamond
    int n = letter - 'A' + 1;  // Number of different letters
    int width = 2 * n - 1;      // Total width/height of diamond
    
    std::vector<std::string> lines;
    
    // Build top half of diamond (including middle)
    for (int i = 0; i < n; i++) {
        char currentLetter = 'A' + i;
        std::string line(width, ' ');
        
        if (i == 0) {
            // First row: single 'A' in the center
            line[width / 2] = 'A';
        } else {
            // Two letters with appropriate spacing
            int outerSpaces = n - i - 1;
            line[outerSpaces] = currentLetter;
            line[width - outerSpaces - 1] = currentLetter;
        }
        
        lines.push_back(line);
    }
    
    // Build bottom half of diamond (mirror of top, excluding middle)
    for (int i = n - 2; i >= 0; i--) {
        lines.push_back(lines[i]);
    }
    
    return lines;
}

}  // namespace diamond
