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
    std::vector<std::string> diamond(size);
    
    // Generate the top half including the middle
    for (int i = 0; i < n; i++) {
        char current_char = 'A' + i;
        std::string line(size, ' ');
        
        // Set the appropriate positions
        int left_pos = (size / 2) - i;
        int right_pos = (size / 2) + i;
        line[left_pos] = current_char;
        line[right_pos] = current_char;
        
        diamond[i] = line;
        diamond[size - 1 - i] = line;
    }
    
    return diamond;
}

}  // namespace diamond
