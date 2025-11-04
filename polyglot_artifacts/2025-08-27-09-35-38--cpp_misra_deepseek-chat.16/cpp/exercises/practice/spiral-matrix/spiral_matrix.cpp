#include "spiral_matrix.h"
#include <vector>
#include <cstdint>

namespace spiral_matrix {

std::vector<std::vector<int>> spiral_matrix(int size) {
    // Since the interface uses int, we need to be careful with the implementation
    // Check for non-negative size
    if (size <= 0) {
        return {};
    }
    
    // Cast to a fixed-width type for internal use
    const std::int32_t n = static_cast<std::int32_t>(size);
    
    // Initialize the matrix with zeros
    std::vector<std::vector<int>> matrix(static_cast<std::size_t>(n), 
                                         std::vector<int>(static_cast<std::size_t>(n), 0));
    
    // Define directions: right, down, left, up
    const std::int32_t directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    std::int32_t current_direction = 0;
    std::int32_t row = 0;
    std::int32_t col = 0;
    
    for (std::int32_t i = 1; i <= (n * n); i++) {
        // Assign the current value - cast indices to size_t
        matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)] = static_cast<int>(i);
        
        // Calculate next position
        std::int32_t next_row = row + directions[current_direction][0];
        std::int32_t next_col = col + directions[current_direction][1];
        
        // Check if next position is invalid (out of bounds or already filled)
        // Add parentheses to ensure proper precedence
        if ((next_row < 0) || (next_row >= n) || (next_col < 0) || (next_col >= n) 
            || (matrix[static_cast<std::size_t>(next_row)][static_cast<std::size_t>(next_col)] != 0)) {
            // Change direction
            current_direction = (current_direction + 1) % 4;
            // Recalculate next position with new direction
            next_row = row + directions[current_direction][0];
            next_col = col + directions[current_direction][1];
        }
        
        row = next_row;
        col = next_col;
    }
    
    return matrix;
}

}  // namespace spiral_matrix
