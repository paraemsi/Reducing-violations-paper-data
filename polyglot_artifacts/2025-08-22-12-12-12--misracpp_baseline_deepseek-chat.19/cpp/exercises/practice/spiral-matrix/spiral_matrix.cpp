#include "spiral_matrix.h"
#include <vector>

namespace spiral_matrix {

    std::vector<std::vector<int> > spiral_matrix(int size) {
        // Handle edge case
        if (size == 0) {
            return std::vector<std::vector<int> >();
        }
        
        // Initialize the matrix with zeros
        std::vector<std::vector<int> > matrix(size, std::vector<int>(size, 0));
        
        int num = 1;
        int top = 0, bottom = size - 1;
        int left = 0, right = size - 1;
        
        while (top <= bottom && left <= right) {
            // Traverse from left to right along the top
            for (int i = left; i <= right; ++i) {
                matrix[top][i] = num++;
            }
            ++top;
            
            // Traverse from top to bottom along the right
            for (int i = top; i <= bottom; ++i) {
                matrix[i][right] = num++;
            }
            --right;
            
            // Make sure we're still within bounds
            if (top <= bottom) {
                // Traverse from right to left along the bottom
                for (int i = right; i >= left; --i) {
                    matrix[bottom][i] = num++;
                }
                --bottom;
            }
            
            // Make sure we're still within bounds
            if (left <= right) {
                // Traverse from bottom to top along the left
                for (int i = bottom; i >= top; --i) {
                    matrix[i][left] = num++;
                }
                ++left;
            }
        }
        
        return matrix;
    }

}  // namespace spiral_matrix
