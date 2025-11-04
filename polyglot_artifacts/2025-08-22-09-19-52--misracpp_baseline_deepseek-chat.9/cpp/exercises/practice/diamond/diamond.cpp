#include "diamond.h"
#include <vector>
#include <string>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter == 'A') {
        return std::vector<std::string>{"A"};
    }
    
    int n = letter - 'A';
    int size = 2 * n + 1;
    std::vector<std::string> diamond;
    
    // Build the top half including the middle
    for (int i = 0; i <= n; i++) {
        std::string row(size, ' ');
        char current_char = 'A' + i;
        
        // Set the appropriate positions
        int left_pos = n - i;
        int right_pos = n + i;
        row[left_pos] = current_char;
        row[right_pos] = current_char;
        
        diamond.push_back(row);
    }
    
    // Build the bottom half by mirroring the top (excluding the middle)
    for (int i = n - 1; i >= 0; i--) {
        diamond.push_back(diamond[i]);
    }
    
    return diamond;
}

}  // namespace diamond
