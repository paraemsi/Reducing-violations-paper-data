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
    
    // Define direction vectors: right, down, left, up
    const std::int32_t dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    std::int32_t row = 0;
    std::int32_t col = 0;
    std::int32_t dir_index = 0;
    
    for (std::uint32_t num = 1U; num <= size * size; num++) {
        matrix[row][col] = num;
        
        // Calculate next position
        std::int32_t next_row = row + dirs[dir_index][0];
        std::int32_t next_col = col + dirs[dir_index][1];
        
        // If next position is out of bounds or already filled, change direction
        if ((next_row < 0) || (next_row >= static_cast<std::int32_t>(size)) || 
            (next_col < 0) || (next_col >= static_cast<std::int32_t>(size)) || 
            (matrix[next_row][next_col] != 0U)) {
            dir_index = (dir_index + 1) % 4;
            next_row = row + dirs[dir_index][0];
            next_col = col + dirs[dir_index][1];
        }
        
        row = next_row;
        col = next_col;
    }
    
    return matrix;
}

}  // namespace spiral_matrix
