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
    int32_t dx[] = {0, 1, 0, -1};
    int32_t dy[] = {1, 0, -1, 0};
    
    std::uint32_t x = 0U;
    std::uint32_t y = 0U;
    int32_t direction = 0;
    std::uint32_t num = 1U;
    
    while (num <= (size * size)) {
        matrix[x][y] = num;
        num++;
        
        // Calculate next position
        std::uint32_t next_x = x + dx[direction];
        std::uint32_t next_y = y + dy[direction];
        
        // If next position is out of bounds or already filled, change direction
        if ((next_x >= size) || (next_y >= size) || (matrix[next_x][next_y] != 0U)) {
            direction = (direction + 1) % 4;
            next_x = x + dx[direction];
            next_y = y + dy[direction];
        }
        
        x = next_x;
        y = next_y;
    }
    
    return matrix;
}

}  // namespace spiral_matrix
