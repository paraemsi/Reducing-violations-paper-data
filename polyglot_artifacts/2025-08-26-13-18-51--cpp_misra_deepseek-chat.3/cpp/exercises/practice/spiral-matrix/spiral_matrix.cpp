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
    
    std::int32_t num = 1;
    std::int32_t top = 0;
    std::int32_t bottom = static_cast<std::int32_t>(size) - 1;
    std::int32_t left = 0;
    std::int32_t right = static_cast<std::int32_t>(size) - 1;
    
    while (top <= bottom && left <= right) {
        // Move right
        for (std::int32_t i = left; i <= right; i++) {
            matrix[static_cast<std::uint32_t>(top)][static_cast<std::uint32_t>(i)] = static_cast<std::uint32_t>(num);
            num++;
        }
        top++;
        
        // Move down
        for (std::int32_t i = top; i <= bottom; i++) {
            matrix[static_cast<std::uint32_t>(i)][static_cast<std::uint32_t>(right)] = static_cast<std::uint32_t>(num);
            num++;
        }
        right--;
        
        // Move left
        if (top <= bottom) {
            for (std::int32_t i = right; i >= left; i--) {
                matrix[static_cast<std::uint32_t>(bottom)][static_cast<std::uint32_t>(i)] = static_cast<std::uint32_t>(num);
                num++;
            }
            bottom--;
        }
        
        // Move up
        if (left <= right) {
            for (std::int32_t i = bottom; i >= top; i--) {
                matrix[static_cast<std::uint32_t>(i)][static_cast<std::uint32_t>(left)] = static_cast<std::uint32_t>(num);
                num++;
            }
            left++;
        }
    }
    
    return matrix;
}

}  // namespace spiral_matrix
