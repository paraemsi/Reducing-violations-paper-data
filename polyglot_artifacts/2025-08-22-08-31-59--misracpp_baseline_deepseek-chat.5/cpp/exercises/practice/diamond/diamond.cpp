#include "diamond.h"
#include <vector>
#include <string>
#include <algorithm>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    int n = letter - 'A' + 1;
    int size = 2 * n - 1;
    std::vector<std::string> diamond;
    
    // Generate top half including the middle
    for (int i = 0; i < n; i++) {
        std::string row(size, ' ');
        char current_char = 'A' + i;
        
        // Set the appropriate positions
        int left_pos = (size / 2) - i;
        int right_pos = (size / 2) + i;
        row[left_pos] = current_char;
        row[right_pos] = current_char;
        
        diamond.push_back(row);
    }
    
    // Generate bottom half by mirroring the top (excluding the middle)
    for (int i = n - 2; i >= 0; i--) {
        diamond.push_back(diamond[i]);
    }
    
    return diamond;
}

}  // namespace diamond
