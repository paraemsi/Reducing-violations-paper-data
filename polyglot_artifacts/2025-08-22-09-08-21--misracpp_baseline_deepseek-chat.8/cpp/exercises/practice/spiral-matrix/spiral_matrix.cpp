#include "spiral_matrix.h"
#include <vector>

namespace spiral_matrix {

std::vector<std::vector<int>> spiral_matrix(int size) {
    if (size == 0) return {};
    
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
    int num = 1;
    int row = 0, col = 0;
    int dr = 0, dc = 1;  // Start moving right
    
    for (int i = 0; i < size * size; i++) {
        matrix[row][col] = num++;
        
        // Check if next step is out of bounds or already filled
        int next_row = row + dr;
        int next_col = col + dc;
        if (next_row < 0 || next_row >= size || next_col < 0 || next_col >= size || 
            matrix[next_row][next_col] != 0) {
            // Change direction clockwise: (0,1) -> (1,0) -> (0,-1) -> (-1,0)
            int temp = dr;
            dr = dc;
            dc = -temp;
        }
        row += dr;
        col += dc;
    }
    return matrix;
}

}  // namespace spiral_matrix
