#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    std::vector<std::vector<unsigned int>> matrix(size, std::vector<unsigned int>(size, 0));

    unsigned int value = 1;
    int top = 0;
    int bottom = static_cast<int>(size) - 1;
    int left = 0;
    int right = static_cast<int>(size) - 1;

    while (top <= bottom && left <= right) {
        // Top row
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = value++;
        }

        // Right column
        for (int row = top + 1; row <= bottom; ++row) {
            matrix[row][right] = value++;
        }

        // Bottom row
        if (top != bottom) {
            for (int col = right - 1; col >= left; --col) {
                matrix[bottom][col] = value++;
            }
        }

        // Left column
        if (left != right) {
            for (int row = bottom - 1; row > top; --row) {
                matrix[row][left] = value++;
            }
        }

        ++top;
        --bottom;
        ++left;
        --right;
    }

    return matrix;
}

}  // namespace spiral_matrix
