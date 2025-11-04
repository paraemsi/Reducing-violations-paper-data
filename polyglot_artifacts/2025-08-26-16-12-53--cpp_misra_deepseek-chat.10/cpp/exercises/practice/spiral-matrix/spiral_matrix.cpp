#include "spiral_matrix.h"
#include <vector>
#include <cstdint>

namespace spiral_matrix {

std::vector<std::vector<int32>> spiral_matrix(int32 size) {
    if (size == 0) {
        return {};
    }
    
    std::vector<std::vector<int32>> matrix(size, std::vector<int32>(size, 0));
    int32 num = 1;
    int32 top = 0;
    int32 bottom = size - 1;
    int32 left = 0;
    int32 right = size - 1;
    
    while ((top <= bottom) && (left <= right)) {
        // Fill top row
        for (int32 i = left; i <= right; i++) {
            matrix[top][i] = num;
            num++;
        }
        top++;
        
        // Fill right column
        for (int32 i = top; i <= bottom; i++) {
            matrix[i][right] = num;
            num++;
        }
        right--;
        
        // Fill bottom row
        if (top <= bottom) {
            for (int32 i = right; i >= left; i--) {
                matrix[bottom][i] = num;
                num++;
            }
            bottom--;
        }
        
        // Fill left column
        if (left <= right) {
            for (int32 i = bottom; i >= top; i--) {
                matrix[i][left] = num;
                num++;
            }
            left++;
        }
    }
    
    return matrix;
}

}  // namespace spiral_matrix
