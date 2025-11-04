#include "spiral_matrix.h"
#include <vector>

namespace spiral_matrix {

std::vector<std::vector<int>> spiral_matrix(int size) {
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
    if (size == 0) return matrix;
    
    int num = 1;
    int row = 0, col = 0;
    int direction = 0; // 0: right, 1: down, 2: left, 3: up
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    for (int i = 0; i < size * size; i++) {
        matrix[row][col] = num++;
        
        int nextRow = row + directions[direction][0];
        int nextCol = col + directions[direction][1];
        
        // If the next cell is out of bounds or already filled, change direction
        if (nextRow < 0 || nextRow >= size || nextCol < 0 || nextCol >= size || matrix[nextRow][nextCol] != 0) {
            direction = (direction + 1) % 4;
            nextRow = row + directions[direction][0];
            nextCol = col + directions[direction][1];
        }
        
        row = nextRow;
        col = nextCol;
    }
    
    return matrix;
}

}  // namespace spiral_matrix
