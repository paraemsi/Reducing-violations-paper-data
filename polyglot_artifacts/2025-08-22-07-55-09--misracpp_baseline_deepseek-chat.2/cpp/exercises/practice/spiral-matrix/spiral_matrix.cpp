#include "spiral_matrix.h"
#include <vector>
using namespace std;

namespace spiral_matrix {

vector<vector<int>> spiral_matrix(int size) {
    if (size == 0) return {};
    
    vector<vector<int>> matrix(size, vector<int>(size, 0));
    int num = 1;
    int row = 0, col = 0;
    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};
    int direction = 0;
    
    for (int i = 0; i < size * size; i++) {
        matrix[row][col] = num++;
        int nextRow = row + dr[direction];
        int nextCol = col + dc[direction];
        
        // If the next cell is invalid or already filled, change direction
        if (nextRow < 0 || nextRow >= size || nextCol < 0 || nextCol >= size || 
            matrix[nextRow][nextCol] != 0) {
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
