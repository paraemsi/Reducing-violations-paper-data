#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral_matrix(std::size_t size) {
    matrix_t matrix(size, std::vector<unsigned int>(size, 0));

    int n = static_cast<int>(size);
    if (n == 0) {
        return matrix;  // Empty matrix requested
    }

    unsigned int value = 1;
    int top    = 0;
    int bottom = n - 1;
    int left   = 0;
    int right  = n - 1;

    while (top <= bottom && left <= right) {
        // Left → Right along the top row
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = value++;
        }
        ++top;

        // Top ↓ Bottom along the right column
        for (int row = top; row <= bottom; ++row) {
            matrix[row][right] = value++;
        }
        --right;

        // Right ← Left along the bottom row
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[bottom][col] = value++;
            }
            --bottom;
        }

        // Bottom ↑ Top along the left column
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
