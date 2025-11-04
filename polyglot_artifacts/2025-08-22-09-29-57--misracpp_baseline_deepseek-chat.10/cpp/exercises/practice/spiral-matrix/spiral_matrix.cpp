#include "spiral_matrix.h"
#include <vector>

namespace spiral_matrix {

std::vector<std::vector<int>> spiral_matrix(int size) {
    if (size == 0) {
        return {};
    }
    
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
    int num = 1;
    int top = 0, bottom = size - 1;
    int left = 0, right = size - 1;
    
    while (num <= size * size) {
        // Fill from left to right along the top
        for (int i = left; i <= right && num <= size * size; i++) {
            matrix[top][i] = num++;
        }
        top++;
        
        // Fill from top to bottom along the right
        for (int i = top; i <= bottom && num <= size * size; i++) {
            matrix[i][right] = num++;
        }
        right--;
        
        // Fill from right to left along the bottom
        for (int i = right; i >= left && num <= size * size; i--) {
            matrix[bottom][i] = num++;
        }
        bottom--;
        
        // Fill from bottom to top along the left
        for (int i = bottom; i >= top && num <= size * size; i--) {
            matrix[i][left] = num++;
        }
        left++;
    }
    
    return matrix;
}

}  // namespace spiral_matrix
