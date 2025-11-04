#include "diamond.h"
#include <vector>
#include <string>
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
        int current_char = 'A' + i;
        int left = n - i;
        int right = n + i;
        row[left] = current_char;
        row[right] = current_char;
        result.push_back(row);
    }
    
    // Add the bottom part (mirror of the top part except the middle)
    for (int i = n - 1; i >= 0; i--) {
        result.push_back(result[i]);
    }
    
    return result;
}

}  // namespace diamond
