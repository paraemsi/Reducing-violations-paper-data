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
        // Traverse from left to right along the top
        for (std::uint32_t i = left; i <= right; i++) {
            matrix[top][i] = num;
            num++;
        }
        top++;
        
        // Traverse from top to bottom along the right
        for (std::uint32_t i = top; i <= bottom; i++) {
            matrix[i][right] = num;
            num++;
        }
        
        if (top <= bottom) {
            // Traverse from right to left along the bottom
            for (std::uint32_t i = right; i > left; i--) {
                if (i == 0U) { 
                    break; 
                }
                matrix[bottom][i - 1U] = num;
                num++;
            }
        } else {
            break;
        }
        
        if (left < right) {
            // Traverse from bottom to top along the left
            for (std::uint32_t i = bottom; i > top; i--) {
                if (i == 0U) { 
                    break; 
                }
                matrix[i - 1U][left] = num;
                num++;
            }
        } else {
            break;
        }
        
        // Update boundaries to move inward
        if (right == 0U) { 
            break; 
        }
        right--;
        if (bottom == 0U) { 
            break; 
        }
        bottom--;
        left++;
    }
    
    return matrix;
}

}  // namespace spiral_matrix
