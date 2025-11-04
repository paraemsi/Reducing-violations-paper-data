#include "diamond.h"
#include <vector>
#include <string>
#include <cmath>
using namespace std;

namespace diamond {

vector<string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    int n = letter - 'A';
    int size = 2 * n + 1;
    vector<string> result;
    
    // Generate each row
    for (int i = 0; i <= n; i++) {
        char current_char = 'A' + i;
        int num_leading_spaces = n - i;
        string row;
        
        // Add leading spaces
        row.append(num_leading_spaces, ' ');
        
        // Add the first character
        row += current_char;
        
        // Add middle spaces if not 'A'
        if (current_char != 'A') {
            int num_middle_spaces = 2 * i - 1;
            row.append(num_middle_spaces, ' ');
            // Add the second character
            row += current_char;
        }
        
        // Add trailing spaces to make sure the length is consistent? No, the test expects exact matches
        // The trailing spaces are the same as leading spaces due to symmetry
        // But the implementation above may not produce strings of equal length
        row.append(num_leading_spaces, ' ');
        result.push_back(row);
    }
    
    // Add the bottom half by mirroring the top half (excluding the middle)
    for (int i = n - 1; i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
