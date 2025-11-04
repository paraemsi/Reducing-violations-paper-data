#include "spiral_matrix.h"
#include <vector>
#include <cstdint>

namespace spiral_matrix {

std::vector<std::vector<std::uint32_t>> spiral_matrix(std::uint32_t size) {
    if (size == 0) {
        return {};
    }
    
    // Initialize the matrix with zeros
    std::vector<std::vector<std::uint32_t>> matrix(size, std::vector<std::uint32_t>(size, 0));
    
    std::uint32_t num = 1;
    std::uint32_t top = 0;
    std::uint32_t bottom = size - 1;
    std::uint32_t left = 0;
    std::uint32_t right = size - 1;
    
    while (num <= (size * size)) {
        // Fill top row from left to right
        for (std::uint32_t i = left; i <= right; i++) {
            matrix[top][i] = num;
            num++;
        }
        top++;
        
        // Fill right column from top to bottom
        for (std::uint32_t i = top; i <= bottom; i++) {
            matrix[i][right] = num;
            num++;
        }
        // Check to prevent underflow
        if (right == 0) {
            break;
        }
        right--;
        
        // Fill bottom row from right to left
        for (std::uint32_t i = right; i >= left; i--) {
            matrix[bottom][i] = num;
            num++;
            if (i == 0) break; // Prevent underflow when i is 0 and condition i >= left is true
        }
        // Check to prevent underflow
        if (bottom == 0) {
            break;
        }
        bottom--;
        
        // Fill left column from bottom to top
        for (std::uint32_t i = bottom; i >= top; i--) {
            matrix[i][left] = num;
            num++;
            if (i == 0) break; // Prevent underflow when i is 0 and condition i >= top is true
        }
        left++;
    }
    
    return matrix;
}

}  // namespace spiral_matrix
