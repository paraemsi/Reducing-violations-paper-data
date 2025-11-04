#include "diamond.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

namespace diamond {

vector<string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    int n = letter - 'A';
    int size = 2 * n + 1;
    vector<string> result;
    
    // Generate top part up to the middle
    for (int i = 0; i <= n; i++) {
        char current_char = 'A' + i;
        string line(size, ' ');
        
        // Calculate positions
        int left_pos = n - i;
        int right_pos = n + i;
        
        line[left_pos] = current_char;
        // For rows beyond 'A', we need to set the right position
        if (i > 0) {
            line[right_pos] = current_char;
        }
        result.push_back(line);
    }
    
    // Generate bottom part by mirroring the top part (excluding the middle)
    for (int i = n - 1; i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
