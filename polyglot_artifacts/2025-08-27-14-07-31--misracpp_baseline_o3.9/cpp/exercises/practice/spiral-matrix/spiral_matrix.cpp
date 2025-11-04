#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    std::vector<std::vector<unsigned int>> matrix(size,
                                                 std::vector<unsigned int>(size));

    int n = static_cast<int>(size);


    int left = 0;
    int right = n - 1;
    int top = 0;
    int bottom = n - 1;
    unsigned int value = 1;

    while (left <= right && top <= bottom) {
        // Top row: left -> right
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = value++;
        }
        ++top;

        // Right column: top -> bottom
        for (int row = top; row <= bottom; ++row) {
            matrix[row][right] = value++;
        }
        --right;

        // Bottom row: right -> left
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[bottom][col] = value++;
            }
            --bottom;
        }

        // Left column: bottom -> top
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
