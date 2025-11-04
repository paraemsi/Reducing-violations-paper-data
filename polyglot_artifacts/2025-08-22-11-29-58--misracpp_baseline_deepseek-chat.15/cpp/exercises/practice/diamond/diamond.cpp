#include "diamond.h"
#include <vector>
#include <string>
using namespace std;

namespace diamond {

vector<string> rows(char letter) {
    vector<string> diamond;
    if (letter == 'A') {
        diamond.push_back("A");
        return diamond;
    }
    
    int n = letter - 'A';
    
    // Generate top part including the middle
    for (int i = 0; i <= n; i++) {
        char current_char = 'A' + i;
        string row;
        
        // Add leading spaces
        row.append(string(n - i, ' '));
        
        // Add the first character
        row += current_char;
        
        // Add middle spaces and second character (if not 'A')
        if (i > 0) {
            row.append(string(2 * i - 1, ' '));
            row += current_char;
        }
        
        // Add trailing spaces
        row.append(string(n - i, ' '));
        
        diamond.push_back(row);
    }
    
    // Generate bottom part by mirroring the top part (excluding the middle)
    for (int i = n - 1; i >= 0; i--) {
        diamond.push_back(diamond[i]);
    }
    
    return diamond;
}

}  // namespace diamond
