#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(int n) {
    std::vector<std::vector<unsigned int>> matrix(n, std::vector<unsigned int>(n, 0));
    if (n == 0) return matrix;
    
    unsigned int num = 1;
    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    
    while (top <= bottom && left <= right) {
        // Traverse right
        for (int i = left; i <= right; ++i) {
            matrix[top][i] = num++;
        }
        ++top;
        
        // Traverse down
        for (int i = top; i <= bottom; ++i) {
            matrix[i][right] = num++;
        }
        --right;
        
        // Traverse left, if necessary
        if (top <= bottom) {
            for (int i = right; i >= left; --i) {
                matrix[bottom][i] = num++;
            }
            --bottom;
        }
        
        // Traverse up, if necessary
        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                matrix[i][left] = num++;
            }
            ++left;
        }
    }
    
    return matrix;
}

}  // namespace spiral_matrix
