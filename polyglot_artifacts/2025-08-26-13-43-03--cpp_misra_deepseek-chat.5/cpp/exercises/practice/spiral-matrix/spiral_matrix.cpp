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
    // Use int32_t for indices that can be negative
    std::int32_t top = 0;
    std::int32_t bottom = static_cast<std::int32_t>(size) - 1;
    std::int32_t left = 0;
    std::int32_t right = static_cast<std::int32_t>(size) - 1;
    
    while ((top <= bottom) && (left <= right)) {
        // Fill top row
        for (std::int32_t i = left; i <= right; ++i) {
            matrix[static_cast<std::uint32_t>(top)][static_cast<std::uint32_t>(i)] = num;
            ++num;
        }
        ++top;
        
        // Fill right column
        for (std::int32_t i = top; i <= bottom; ++i) {
            matrix[static_cast<std::uint32_t>(i)][static_cast<std::uint32_t>(right)] = num;
            ++num;
        }
        --right;
        
        // Fill bottom row
        if (top <= bottom) {
            for (std::int32_t i = right; i >= left; --i) {
                matrix[static_cast<std::uint32_t>(bottom)][static_cast<std::uint32_t>(i)] = num;
                ++num;
            }
            --bottom;
        }
        
        // Fill left column
        if (left <= right) {
            for (std::int32_t i = bottom; i >= top; --i) {
                matrix[static_cast<std::uint32_t>(i)][static_cast<std::uint32_t>(left)] = num;
                ++num;
            }
            ++left;
        }
    }
    
    return matrix;
}

}  // namespace spiral_matrix
