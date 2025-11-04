#include "spiral_matrix.h"
#include <vector>
#include <cstdint>

namespace spiral_matrix {
namespace impl {

std::vector<std::vector<std::uint32_t>> generate_spiral(std::uint32_t size) {
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
    
    while ((top <= bottom) && (left <= right)) {
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
            // To avoid issues with unsigned integers when decrementing, we'll use a signed integer for the loop counter
            // But we need to cast carefully to follow MISRA rules
            for (std::int32_t i = static_cast<std::int32_t>(right); 
                 i >= static_cast<std::int32_t>(left); 
                 i--) {
                matrix[bottom][static_cast<std::uint32_t>(i)] = num;
                num++;
            }
            bottom--;
        }
        
        // Fill left column from bottom to top
        if (left <= right) {
            for (std::int32_t i = static_cast<std::int32_t>(bottom); 
                 i >= static_cast<std::int32_t>(top); 
                 i--) {
                matrix[static_cast<std::uint32_t>(i)][left] = num;
                num++;
            }
            left++;
        }
    }
    
    return matrix;
}

}  // namespace impl
}  // namespace spiral_matrix
