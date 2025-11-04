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
    
    while (num <= size * size) {
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
        
        // Fill bottom row from right to left
        if (top <= bottom) {
            for (std::uint32_t i = right; i >= left; i--) {
                // To prevent underflow when i is 0 and we decrement past 0, we need to be careful
                // Since i is unsigned, we can't have i >= left when left is 0 and i becomes -1
                // But the condition i >= left will always be true if i wraps around to a large number
                // So we need to break if i > right (which would happen if it underflows)
                // Let's use a different approach
                if (i > right) {
                    break;
                }
                matrix[bottom][i] = num;
                num++;
                if (i == 0U) {
                    break;
                }
            }
        }
        bottom--;
        
        // Fill left column from bottom to top
        if (left <= right) {
            for (std::uint32_t i = bottom; i >= top; i--) {
                if (i > bottom) {
                    break;
                }
                matrix[i][left] = num;
                num++;
                if (i == 0U) {
                    break;
                }
            }
        }
        left++;
    }
    
    return matrix;
}

}  // namespace spiral_matrix
