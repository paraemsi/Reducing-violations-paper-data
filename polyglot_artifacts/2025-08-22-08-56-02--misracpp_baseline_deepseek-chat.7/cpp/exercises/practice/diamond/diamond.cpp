#include "diamond.h"
#include <vector>
#include <string>
using namespace std;

namespace diamond {

vector<string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    int n = letter - 'A' + 1;
    int total_rows = 2 * n - 1;
    vector<string> diamond(total_rows);
    
    // Generate top half including the middle
    for (int i = 0; i < n; i++) {
        char current_char = 'A' + i;
        string& row = diamond[i];
        
        // Leading spaces
        int leading_spaces = n - i - 1;
        row.append(leading_spaces, ' ');
        
        // First character
        row += current_char;
        
        if (current_char != 'A') {
            // Middle spaces
            int middle_spaces = 2 * i - 1;
            row.append(middle_spaces, ' ');
            // Second character
            row += current_char;
        }
        
        // Trailing spaces
        row.append(leading_spaces, ' ');
    }
    
    // Mirror the top half to the bottom half
    for (int i = n; i < total_rows; i++) {
        diamond[i] = diamond[total_rows - i - 1];
    }
    
    return diamond;
}

}  // namespace diamond
