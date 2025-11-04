#include "diamond.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

namespace diamond {

vector<string> rows(char letter) {
    vector<string> result;
    if (letter == 'A') {
        result.push_back("A");
        return result;
    }
    
    int n = letter - 'A';
    int size = 2 * n + 1;
    
    // Generate each row
    for (int i = 0; i <= n; i++) {
        string row(size, ' ');
        char current_char = 'A' + i;
        
        // Calculate positions
        int left_pos = n - i;
        int right_pos = n + i;
        row[left_pos] = current_char;
        row[right_pos] = current_char;
        result.push_back(row);
    }
    
    // Add the bottom part by mirroring the top part (excluding the middle)
    for (int i = n - 1; i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
