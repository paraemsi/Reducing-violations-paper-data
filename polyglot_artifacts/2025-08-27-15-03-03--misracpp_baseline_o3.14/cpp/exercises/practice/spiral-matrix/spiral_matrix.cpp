#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> generate(std::size_t size) {
    if (size == 0) {
        return {};
    }

    const int n = static_cast<int>(size);
    std::vector<std::vector<unsigned int>> matrix(n, std::vector<unsigned int>(n, 0U));

    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;
    unsigned int current = 1U;

    while (top <= bottom && left <= right) {
        // Traverse from left to right along the top row
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = current++;
        }
        ++top;

        // Traverse from top to bottom along the right column
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

        // Traverse from bottom to top along the left column
        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                matrix[row][left] = current++;
            }
            ++left;
        }
    }

    return matrix;
}

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    // Reuse the already tested generate() implementation
    return generate(size);
}

}  // namespace spiral_matrix
