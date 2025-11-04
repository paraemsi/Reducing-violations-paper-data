#include "spiral_matrix.h"
#include <vector>
#include <cstdint>

namespace spiral_matrix {

std::vector<std::vector<std::uint32_t>> spiral_matrix(std::uint32_t size) {
    if (size == 0) {
        return {};
    }
    
    std::vector<std::vector<std::uint32_t>> matrix(size, std::vector<std::uint32_t>(size, 0));
    
    // Define direction vectors for right, down, left, up
    const std::int32_t dx[] = {0, 1, 0, -1};
    const std::int32_t dy[] = {1, 0, -1, 0};
    
    std::int32_t x = 0;
    std::int32_t y = -1;
    std::int32_t dir = 0;
    std::uint32_t current = 1;
    std::uint32_t total = size * size;
    
    while (current <= total) {
        std::int32_t next_x = x + dx[dir];
        std::int32_t next_y = y + dy[dir];
        
        // Check if the next cell is within bounds and not filled
        if ((next_x >= 0) && (next_x < static_cast<std::int32_t>(size)) && 
            (next_y >= 0) && (next_y < static_cast<std::int32_t>(size)) && 
            (matrix[next_x][next_y] == 0)) {
            x = next_x;
            y = next_y;
            matrix[x][y] = current;
            current++;
        } else {
            // Change direction
            dir = (dir + 1) % 4;
        }
    }
    
    return matrix;
}

}  // namespace spiral_matrix
