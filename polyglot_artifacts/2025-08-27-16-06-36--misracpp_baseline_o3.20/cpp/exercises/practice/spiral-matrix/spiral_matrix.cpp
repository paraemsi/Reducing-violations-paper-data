#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    const int n = static_cast<int>(size);
    std::vector<std::vector<unsigned int>> matrix(size, std::vector<unsigned int>(size));

    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;
    unsigned int value = 1;

    while (left <= right && top <= bottom) {
        // Traverse from left to right across the top row
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = value++;
        }
        // Traverse down the rightmost column
        for (int row = top + 1; row <= bottom; ++row) {
            matrix[row][right] = value++;
        }
        // Traverse from right to left across the bottom row
        if (top < bottom) {
            for (int col = right - 1; col >= left; --col) {
                matrix[bottom][col] = value++;
            }
        }
        // Traverse up the leftmost column
        if (left < right) {
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
