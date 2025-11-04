#include "diamond.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

namespace diamond {

vector<string> rows(char letter) {
    vector<string> result;
    int n = letter - 'A';
    int size = 2 * n + 1;
    
    // Generate each row
    for (int i = 0; i <= n; i++) {
        char current_char = 'A' + i;
        string line;
        
        // Add leading spaces
        line.append(string(n - i, ' '));
        
        // Add the first character
        line += current_char;
        
        // Add middle spaces and second character (if not 'A')
        if (i > 0) {
            line.append(string(2 * i - 1, ' '));
            line += current_char;
        }
        
        // Add trailing spaces
        line.append(string(n - i, ' '));
        
        result.push_back(line);
    }
    
    // Add the bottom half by mirroring the top half (excluding the middle)
    for (int i = n - 1; i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
