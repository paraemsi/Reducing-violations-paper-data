#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    const int n = static_cast<int>(size);
    std::vector<std::vector<unsigned int>> matrix(n, std::vector<unsigned int>(n, 0));

    unsigned int value = 1;
    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;

    while (top <= bottom && left <= right) {
        // Move right
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = value++;
        }
        ++top;

        // Move down
        for (int row = top; row <= bottom; ++row) {
            matrix[row][right] = value++;
        }
        --right;

        // Move left
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[bottom][col] = value++;
            }
            --bottom;
        }

        // Move up
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
