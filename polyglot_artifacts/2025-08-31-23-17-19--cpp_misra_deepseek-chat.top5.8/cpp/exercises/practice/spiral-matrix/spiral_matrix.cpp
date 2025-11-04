#include "spiral_matrix.h"
#include <vector>
#include <cstdint>

namespace spiral_matrix {

std::vector<std::vector<std::uint32_t>> spiral_matrix(std::uint32_t size) {
    if (size == 0) {
        return {};
    }
    
    std::vector<std::vector<std::uint32_t>> matrix(size, std::vector<std::uint32_t>(size, 0));
    std::uint32_t num = 1;
    std::int32_t top = 0;
    std::int32_t bottom = static_cast<std::int32_t>(size) - 1;
    std::int32_t left = 0;
    std::int32_t right = static_cast<std::int32_t>(size) - 1;
    
    while (top <= bottom && left <= right) {
        // Fill top row
        for (std::int32_t i = left; i <= right; i++) {
            matrix[top][i] = num;
            num++;
        }
        top++;
        
        // Fill right column
        for (std::int32_t i = top; i <= bottom; i++) {
            matrix[i][right] = num;
            num++;
        }
        right--;
        
        if (top <= bottom) {
            // Fill bottom row
            for (std::int32_t i = right; i >= left; i--) {
                matrix[bottom][i] = num;
                num++;
            }
            bottom--;
        }
        
        if (left <= right) {
            // Fill left column
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
