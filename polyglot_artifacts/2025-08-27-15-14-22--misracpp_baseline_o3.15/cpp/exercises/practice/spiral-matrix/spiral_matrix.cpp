#include "spiral_matrix.h"
#include <vector>
#include <cstddef>

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    std::vector<std::vector<unsigned int>> matrix(
        static_cast<std::size_t>(size),
        std::vector<unsigned int>(static_cast<std::size_t>(size), 0));

    if (size == 0) {
        return matrix;
    }

    int n = static_cast<int>(size);
    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;
    int value = 1;

    while (top <= bottom && left <= right) {
        // Traverse from left to right.
        for (int col = left; col <= right; ++col) {
            matrix[top][static_cast<std::size_t>(col)] = value++;
        }
        ++top;

        // Traverse from top to bottom.
        for (int row = top; row <= bottom; ++row) {
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = value++;
        }
        --right;

        // Traverse from right to left.
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = value++;
            }
            --bottom;
        }

        // Traverse from bottom to top.
        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(left)] = value++;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
