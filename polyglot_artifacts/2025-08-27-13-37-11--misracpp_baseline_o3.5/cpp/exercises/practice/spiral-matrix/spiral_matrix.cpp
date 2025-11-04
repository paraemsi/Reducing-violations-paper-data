#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    int n = static_cast<int>(size);
    std::vector<std::vector<unsigned int>> matrix(size, std::vector<unsigned int>(size, 0));

    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;
    unsigned int current = 1;

    while (top <= bottom && left <= right) {
        // Traverse from left to right along the top row
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = current++;
        }
        ++top;

        // Traverse from top to bottom along the rightmost column
        for (int row = top; row <= bottom; ++row) {
            matrix[row][right] = current++;
        }
        --right;

        // Traverse from right to left along the bottom row
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[bottom][col] = current++;
            }
            --bottom;
        }

        // Traverse from bottom to top along the leftmost column
        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                matrix[row][left] = current++;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
