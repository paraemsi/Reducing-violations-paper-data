#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(int size) {
    if (size <= 0) {
        return {};
    }

    std::vector<std::vector<unsigned int>> matrix(size,
                                                  std::vector<unsigned int>(size, 0));

    int top = 0;
    int bottom = size - 1;
    int left = 0;
    int right = size - 1;
    unsigned int current = 1;
    const unsigned int limit =
        static_cast<unsigned int>(size) * static_cast<unsigned int>(size);

    while (current <= limit) {
        // Traverse from left to right along the top row.
        for (int col = left; col <= right && current <= limit; ++col) {
            matrix[top][col] = current++;
        }
        ++top;

        // Traverse from top to bottom along the right column.
        for (int row = top; row <= bottom && current <= limit; ++row) {
            matrix[row][right] = current++;
        }
        --right;

        // Traverse from right to left along the bottom row.
        for (int col = right; col >= left && current <= limit; --col) {
            matrix[bottom][col] = current++;
        }
        --bottom;

        // Traverse from bottom to top along the left column.
        for (int row = bottom; row >= top && current <= limit; --row) {
            matrix[row][left] = current++;
        }
        ++left;
    }

    return matrix;
}

}  // namespace spiral_matrix
