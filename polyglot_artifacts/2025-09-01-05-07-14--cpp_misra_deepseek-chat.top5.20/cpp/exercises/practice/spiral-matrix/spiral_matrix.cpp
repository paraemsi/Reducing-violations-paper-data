#include "spiral_matrix.h"
#include <vector>
#include <cstdint>

namespace spiral_matrix {

matrix_t spiral_matrix(std::int32_t size) {
    if (size == 0) {
        return {};
    }
    
    // Initialize the matrix with zeros
    matrix_t matrix(size, std::vector<std::int32_t>(size, 0));
    
    std::int32_t num = 1;
    std::int32_t top = 0;
    std::int32_t bottom = size - 1;
    std::int32_t left = 0;
    std::int32_t right = size - 1;
    
    while ((top <= bottom) && (left <= right)) {
        // Fill top row from left to right
        for (std::int32_t i = left; i <= right; i++) {
            matrix[top][i] = num;
            num++;
        }
        top++;
        
        // Fill right column from top to bottom
        for (std::int32_t i = top; i <= bottom; i++) {
            matrix[i][right] = num;
            num++;
        }
        right--;
        
        // Fill bottom row from right to left
        if (top <= bottom) {
            for (std::int32_t i = right; i >= left; i--) {
                matrix[bottom][i] = num;
                num++;
            }
            bottom--;
        }
        
        // Fill left column from bottom to top
        if (left <= right) {
            for (std::int32_t i = bottom; i >= top; i--) {
                matrix[i][left] = num;
                num++;
            }
            left++;
        }
    }
    
    return matrix;
}

}  // namespace spiral_matrix
