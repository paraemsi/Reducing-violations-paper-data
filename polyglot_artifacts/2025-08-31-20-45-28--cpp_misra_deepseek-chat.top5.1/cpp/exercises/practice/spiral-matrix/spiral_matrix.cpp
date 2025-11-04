#include "spiral_matrix.h"
#include <vector>
#include <cstdint>

namespace spiral_matrix {

std::vector<std::vector<std::uint32_t>> spiral_matrix(std::uint32_t size) {
    if (size == 0U) {
        return {};
    }
    
    // Initialize the matrix with zeros
    std::vector<std::vector<std::uint32_t>> matrix(size, std::vector<std::uint32_t>(size, 0U));
    
    std::uint32_t num = 1U;
    std::uint32_t top = 0U;
    std::uint32_t bottom = size - 1U;
    std::uint32_t left = 0U;
    std::uint32_t right = size - 1U;
    
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
        right--;
        
        // Check if there's a bottom row to fill
        if (top <= bottom) {
            // Fill bottom row from right to left
            // Since i is unsigned, we need to be careful about the condition
            // We can use a different approach to avoid underflow
            for (std::uint32_t i = right + 1U; i > left; ) {
                i--;
                matrix[bottom][i] = num;
                num++;
            }
            bottom--;
        }
        
        // Check if there's a left column to fill
        if (left <= right) {
            // Fill left column from bottom to top
            for (std::uint32_t i = bottom + 1U; i > top; ) {
                i--;
                matrix[i][left] = num;
                num++;
            }
            left++;
        }
    }
    
    return matrix;
}

}  // namespace spiral_matrix
