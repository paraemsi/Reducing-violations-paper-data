#include "spiral_matrix.h"

namespace spiral_matrix {

Matrix spiral_matrix(int size) {
    if (size <= 0) {
        return Matrix();
    }
    
    // Initialize matrix with zeros
    Matrix matrix(size, std::vector<int>(size, 0));
    
    // Direction vectors: right, down, left, up
    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};
    int direction = 0; // Start moving right
    
    int row = 0, col = 0;
    
    for (int num = 1; num <= size * size; num++) {
        matrix[row][col] = num;
        
        // Don't calculate next position if this was the last number
        if (num == size * size) {
            break;
        }
        
        // Calculate next position
        int nextRow = row + dr[direction];
        int nextCol = col + dc[direction];
        
        // Check if we need to change direction
        // Change direction if: out of bounds OR cell already filled
        if (nextRow < 0 || nextRow >= size || 
            nextCol < 0 || nextCol >= size || 
            matrix[nextRow][nextCol] != 0) {
            
            // Turn clockwise
            direction = (direction + 1) % 4;
            nextRow = row + dr[direction];
            nextCol = col + dc[direction];
        }
        
        row = nextRow;
        col = nextCol;
    }
    
    return matrix;
}

}  // namespace spiral_matrix
