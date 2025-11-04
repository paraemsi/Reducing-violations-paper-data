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
    
    // Define directions: right, down, left, up
    const std::int32_t dx[] = {0, 1, 0, -1};
    const std::int32_t dy[] = {1, 0, -1, 0};
    
    // Use signed integers to prevent underflow
    std::int32_t x = 0;
    std::int32_t y = 0;
    std::uint32_t dir = 0;
    
    for (std::uint32_t i = 1; i <= (size * size); i++) {
        // Cast to unsigned when accessing the matrix
        matrix[static_cast<std::uint32_t>(x)][static_cast<std::uint32_t>(y)] = i;
        
        // Calculate next position
        std::int32_t nextX = x + dx[dir];
        std::int32_t nextY = y + dy[dir];
        
        // Check if next position is out of bounds or already filled
        if ((nextX < 0) || (nextX >= static_cast<std::int32_t>(size)) || 
            (nextY < 0) || (nextY >= static_cast<std::int32_t>(size)) || 
            (matrix[static_cast<std::uint32_t>(nextX)][static_cast<std::uint32_t>(nextY)] != 0)) {
            // Change direction
            dir = (dir + 1U) % 4U;
            nextX = x + dx[dir];
            nextY = y + dy[dir];
        }
        
        x = nextX;
        y = nextY;
    }
    
    return matrix;
}

}  // namespace spiral_matrix
