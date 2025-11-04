#include "spiral_matrix.h"
#include <cstdint>

namespace spiral_matrix {

Matrix spiral_matrix(std::int32_t size) {
    if (size <= 0) {
        return Matrix{};
    }
    
    Matrix result(static_cast<std::size_t>(size), 
                  std::vector<unsigned int>(static_cast<std::size_t>(size), 0));
    
    unsigned int value = 1;
    std::int32_t top = 0;
    std::int32_t bottom = size - 1;
    std::int32_t left = 0;
    std::int32_t right = size - 1;
    
    while ((top <= bottom) && (left <= right)) {
        // Fill top row from left to right
        for (std::int32_t col = left; col <= right; ++col) {
            result[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = value;
            ++value;
        }
        ++top;
        
        // Fill right column from top to bottom
        for (std::int32_t row = top; row <= bottom; ++row) {
            result[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = value;
            ++value;
        }
        --right;
        
        // Fill bottom row from right to left (if there is a bottom row)
        if (top <= bottom) {
            for (std::int32_t col = right; col >= left; --col) {
                result[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = value;
                ++value;
            }
            --bottom;
        }
        
        // Fill left column from bottom to top (if there is a left column)
        if (left <= right) {
            for (std::int32_t row = bottom; row >= top; --row) {
                result[static_cast<std::size_t>(row)][static_cast<std::size_t>(left)] = value;
                ++value;
            }
            ++left;
        }
    }
    
    return result;
}

}  // namespace spiral_matrix
