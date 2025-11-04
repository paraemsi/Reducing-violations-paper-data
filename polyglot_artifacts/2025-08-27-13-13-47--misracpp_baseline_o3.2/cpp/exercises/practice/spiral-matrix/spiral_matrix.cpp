#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<int>> spiral_matrix(int size) {
    if (size <= 0) {
        return {};
    }

    std::vector<std::vector<int>> matrix(size, std::vector<int>(size));
    int top = 0;
    int bottom = size - 1;
    int left = 0;
    int right = size - 1;
    int value = 1;
    const int max_value = size * size;

    while (value <= max_value) {
        // Fill top row from left to right.
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = value++;
        }
        ++top;

        // Fill right column from top to bottom.
        for (int row = top; row <= bottom; ++row) {
            matrix[row][right] = value++;
        }
        --right;

        // Fill bottom row from right to left.
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[bottom][col] = value++;
            }
            --bottom;
        }

        // Fill left column from bottom to top.
        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                matrix[row][left] = value++;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
