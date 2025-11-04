#include "diamond.h"
#include <vector>
#include <string>
using namespace std;

namespace diamond {

vector<string> rows(char letter) {
    if (letter == 'A') {
        return {"A"};
    }
    
    int n = letter - 'A';
    int size = 2 * n + 1;
    vector<string> result;
    
    // Generate top half including middle
    for (int i = 0; i <= n; i++) {
        string line(size, ' ');
        char current_char = 'A' + i;
        
        // Set the positions for the two letters
        int left_pos = n - i;
        int right_pos = n + i;
        line[left_pos] = current_char;
        line[right_pos] = current_char;
        
        result.push_back(line);
    }
    
    // Generate bottom half by mirroring the top (excluding the middle)
    for (int i = n - 1; i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
