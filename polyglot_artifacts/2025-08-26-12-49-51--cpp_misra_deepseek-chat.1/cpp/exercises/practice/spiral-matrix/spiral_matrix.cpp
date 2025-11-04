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
    const int32_t dx[] = {0, 1, 0, -1};
    const int32_t dy[] = {1, 0, -1, 0};
    
    // Use int32_t for indices to handle negative values
    int32_t x = 0;
    int32_t y = 0;
    std::uint32_t dir = 0U; // Start with right direction
    std::uint32_t current_num = 1U;
    
    while (current_num <= (size * size)) {
        // x and y are always within bounds here, so we can cast to uint32_t
        matrix[static_cast<std::uint32_t>(x)][static_cast<std::uint32_t>(y)] = current_num;
        current_num++;
        
        // Calculate next position
        int32_t next_x = x + dx[dir];
        int32_t next_y = y + dy[dir];
        
        // Check if next position is out of bounds or already filled
        if ((next_x < 0) || (next_x >= static_cast<int32_t>(size)) || 
            (next_y < 0) || (next_y >= static_cast<int32_t>(size)) || 
            (matrix[static_cast<std::uint32_t>(next_x)][static_cast<std::uint32_t>(next_y)] != 0U)) {
            // Change direction
            dir = (dir + 1U) % 4U;
            next_x = x + dx[dir];
            next_y = y + dy[dir];
        }
        
        x = next_x;
        y = next_y;
    }
    
    return matrix;
}

}  // namespace spiral_matrix
