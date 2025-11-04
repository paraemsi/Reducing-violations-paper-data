#include "spiral_matrix.h"
#include <vector>

namespace spiral_matrix {

std::vector<std::vector<int>> spiral_matrix(int size) {
    if (size == 0) return {};
    
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
    int num = 1;
    int row = 0, col = 0;
    int direction = 0; // 0: right, 1: down, 2: left, 3: up
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    for (int i = 0; i < size * size; i++) {
        matrix[row][col] = num++;
        
        // Calculate next position
        int next_row = row + directions[direction][0];
        int next_col = col + directions[direction][1];
        
        // If next position is invalid or already filled, change direction
        if (next_row < 0 || next_row >= size || next_col < 0 || next_col >= size || 
            matrix[next_row][next_col] != 0) {
            direction = (direction + 1) % 4;
            next_row = row + directions[direction][0];
            next_col = col + directions[direction][1];
        }
        
        row = next_row;
        col = next_col;
    }
    
    return matrix;
}

}  // namespace spiral_matrix
