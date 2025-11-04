#include "spiral_matrix.h"
#include <vector>

namespace spiral_matrix {

std::vector<std::vector<int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    std::vector<std::vector<int>> matrix(size, std::vector<int>(size));
    int num = 1;
    int top = 0, left = 0;
    int bottom = static_cast<int>(size) - 1;
    int right = static_cast<int>(size) - 1;

    while (top <= bottom && left <= right) {
        // Top row (left -> right)
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = num++;
        }
        ++top;

        // Right column (top -> bottom)
        for (int row = top; row <= bottom; ++row) {
            matrix[row][right] = num++;
        }
        --right;

        // Bottom row (right -> left)
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[bottom][col] = num++;
            }
            --bottom;
        }

        // Left column (bottom -> top)
        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                matrix[row][left] = num++;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
