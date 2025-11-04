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
        // Fill top row
        for (std::uint32_t i = left; i <= right; i++) {
            matrix[top][i] = num;
            num++;
        }
        top++;
        
        // Fill right column
        if (top <= bottom) {
            for (std::uint32_t i = top; i <= bottom; i++) {
                matrix[i][right] = num;
                num++;
            }
            right--;
        } else {
            break;
        }
        
        // Fill bottom row
        if (left <= right) {
            for (std::uint32_t i = right; i >= left; i--) {
                matrix[bottom][i] = num;
                num++;
                if (i == 0U) {  // Prevent underflow
                    break;
                }
            }
            bottom--;
        } else {
            break;
        }
        
        // Fill left column
        if (top <= bottom) {
            for (std::uint32_t i = bottom; i >= top; i--) {
                matrix[i][left] = num;
                num++;
                if (i == 0U) {  // Prevent underflow
                    break;
                }
            }
            left++;
        } else {
            break;
        }
    }
    
    return matrix;
}

}  // namespace spiral_matrix
