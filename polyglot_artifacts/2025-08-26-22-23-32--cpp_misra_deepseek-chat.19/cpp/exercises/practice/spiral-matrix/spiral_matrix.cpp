#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<std::int32_t>> spiral_matrix(std::int32_t size) {
    if (size == 0) {
        return {};
    }
    
    // Initialize the matrix with zeros
    std::vector<std::vector<std::int32_t>> matrix(static_cast<std::size_t>(size), 
                                                 std::vector<std::int32_t>(static_cast<std::size_t>(size), 0));
    
    // Define boundaries
    std::int32_t top = 0;
    std::int32_t bottom = size - 1;
    std::int32_t left = 0;
    std::int32_t right = size - 1;
    
    std::int32_t num = 1;
    
    while ((top <= bottom) && (left <= right)) {
        // Move from left to right along the top
        for (std::int32_t i = left; i <= right; i++) {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(i)] = num;
            num++;
        }
        top++;
        
        // Move from top to bottom along the right
        for (std::int32_t i = top; i <= bottom; i++) {
            matrix[static_cast<std::size_t>(i)][static_cast<std::size_t>(right)] = num;
            num++;
        }
        right--;
        
        // Move from right to left along the bottom
        if (top <= bottom) {
            for (std::int32_t i = right; i >= left; i--) {
                matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(i)] = num;
                num++;
            }
            bottom--;
        }
        
        // Move from bottom to top along the left
        if (left <= right) {
            for (std::int32_t i = bottom; i >= top; i--) {
                matrix[static_cast<std::size_t>(i)][static_cast<std::size_t>(left)] = num;
                num++;
            }
            left++;
        }
    }
    
    return matrix;
}

}  // namespace spiral_matrix
