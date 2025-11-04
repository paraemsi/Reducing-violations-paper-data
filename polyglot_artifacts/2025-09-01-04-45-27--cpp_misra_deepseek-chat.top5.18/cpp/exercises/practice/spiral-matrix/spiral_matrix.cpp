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
        // Move right
        for (std::int32_t i = static_cast<std::int32_t>(left); 
             i <= static_cast<std::int32_t>(right); 
             i++) {
            matrix[top][static_cast<std::uint32_t>(i)] = num;
            num++;
        }
        top++;
        
        // Move down
        for (std::int32_t i = static_cast<std::int32_t>(top); 
             i <= static_cast<std::int32_t>(bottom); 
             i++) {
            matrix[static_cast<std::uint32_t>(i)][right] = num;
            num++;
        }
        if (right > 0) {
            right--;
        } else {
            right = 0;
        }
        
        // Move left
        if (top <= bottom) {
            for (std::int32_t i = static_cast<std::int32_t>(right); 
                 i >= static_cast<std::int32_t>(left); 
                 i--) {
                matrix[bottom][static_cast<std::uint32_t>(i)] = num;
                num++;
            }
            if (bottom > 0) {
                bottom--;
            } else {
                bottom = 0;
            }
        } else {
            // Do nothing
        }
        
        // Move up
        if (left <= right) {
            for (std::int32_t i = static_cast<std::int32_t>(bottom); 
                 i >= static_cast<std::int32_t>(top); 
                 i--) {
                matrix[static_cast<std::uint32_t>(i)][left] = num;
                num++;
            }
            left++;
        } else {
            // Do nothing
        }
    }
    
    return matrix;
}

}  // namespace spiral_matrix
