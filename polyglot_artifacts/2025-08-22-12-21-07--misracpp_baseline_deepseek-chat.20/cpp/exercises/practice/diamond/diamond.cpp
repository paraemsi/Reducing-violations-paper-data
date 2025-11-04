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
    int size = 2 * n - 1;
    vector<string> result(size);
    
    // Generate each row
    for (int i = 0; i < n; i++) {
        char current_char = 'A' + i;
        string row(size, ' ');
        
        // Calculate positions
        int left_pos = n - 1 - i;
        int right_pos = size - n + i;
        row[left_pos] = current_char;
        row[right_pos] = current_char;
        
        result[i] = row;
        result[size - 1 - i] = row;
    }
    
    return result;
}

}  // namespace diamond
