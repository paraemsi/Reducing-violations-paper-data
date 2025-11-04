#include "spiral_matrix.h"
#include <vector>
#include <cstdint>

namespace spiral_matrix {

// Define a signed integer type for indices to handle potential negative values
using index_t = std::int32_t;

matrix_t spiral_matrix(size_type size) {
    if (size == 0U) {
        return {};
    }
    
    // Initialize the matrix with zeros
    matrix_t matrix(size, std::vector<std::uint32_t>(size, 0U));
    
    std::uint32_t num = 1U;
    index_t top = 0;
    index_t bottom = static_cast<index_t>(size) - 1;
    index_t left = 0;
    index_t right = static_cast<index_t>(size) - 1;
    
    while ((top <= bottom) && (left <= right)) {
        // Fill top row from left to right
        for (index_t i = left; i <= right; ++i) {
            matrix[static_cast<size_type>(top)][static_cast<size_type>(i)] = num;
            ++num;
        }
        ++top;
        
        // Fill right column from top to bottom
        for (index_t i = top; i <= bottom; ++i) {
            matrix[static_cast<size_type>(i)][static_cast<size_type>(right)] = num;
            ++num;
        }
        --right;
        
        // Fill bottom row from right to left
        if (top <= bottom) {
            for (index_t i = right; i >= left; --i) {
                matrix[static_cast<size_type>(bottom)][static_cast<size_type>(i)] = num;
                ++num;
            }
            --bottom;
        }
        
        // Fill left column from bottom to top
        if (left <= right) {
            for (index_t i = bottom; i >= top; --i) {
                matrix[static_cast<size_type>(i)][static_cast<size_type>(left)] = num;
                ++num;
            }
            ++left;
        }
    }
    
    return matrix;
}

}  // namespace spiral_matrix
