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
    
    // Define directions: right, down, left, up
    const std::int32_t dx[] = {0, 1, 0, -1};
    const std::int32_t dy[] = {1, 0, -1, 0};
    
    std::int32_t x = 0;
    std::int32_t y = 0;
    std::int32_t direction = 0;
    
    for (std::uint32_t i = 1U; i <= (size * size); i++) {
        matrix[x][y] = i;
        
        // Calculate next position
        std::int32_t next_x = x + dx[direction];
        std::int32_t next_y = y + dy[direction];
        
        // Check if next position is valid (within bounds and not filled)
        if ((next_x < 0) 
            || (next_x >= static_cast<std::int32_t>(size)) 
            || (next_y < 0) 
            || (next_y >= static_cast<std::int32_t>(size)) 
            || (matrix[next_x][next_y] != 0U)) {
            // Change direction
            direction = ((direction + 1) % 4);
            next_x = x + dx[direction];
            next_y = y + dy[direction];
        }
        
        x = next_x;
        y = next_y;
    }
    
    return matrix;
}

}  // namespace spiral_matrix
