#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    // Handle the edge-case of a 0×0 matrix early.
    if (size == 0) {
        return {};
    }

    std::vector<std::vector<unsigned int>> result(size, std::vector<unsigned int>(size, 0));

    int n       = static_cast<int>(size);
    int top     = 0;
    int bottom  = n - 1;
    int left    = 0;
    int right   = n - 1;
    unsigned int current = 1;

    while (top <= bottom && left <= right) {
        // Traverse from left to right across the current top row.
        for (int col = left; col <= right; ++col) {
            result[top][col] = current++;
        }
        ++top;

        // Traverse from top to bottom down the current right column.
        for (int row = top; row <= bottom; ++row) {
            result[row][right] = current++;
        }
        --right;

        // Traverse from right to left across the current bottom row.
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                result[bottom][col] = current++;
            }
            --bottom;
        }

        // Traverse from bottom to top up the current left column.
        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                result[row][left] = current++;
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
