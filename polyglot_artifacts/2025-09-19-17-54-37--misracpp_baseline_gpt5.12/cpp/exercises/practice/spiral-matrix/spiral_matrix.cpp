#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<int>> spiral_matrix(std::size_t size) {
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
    int n = static_cast<int>(size);
    if (n == 0) {
        return matrix;
    }

    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;
    int val = 1;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; ++j) {
            matrix[top][j] = val++;
        }
        ++top;

        for (int i = top; i <= bottom; ++i) {
            matrix[i][right] = val++;
        }
        --right;

        if (top <= bottom) {
            for (int j = right; j >= left; --j) {
                matrix[bottom][j] = val++;
            }
            --bottom;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                matrix[i][left] = val++;
            }
            ++left;
        }
    }

    return matrix;
}

std::vector<std::vector<int>> spiral(std::size_t size) {
    return spiral_matrix(size);
}

}  // namespace spiral_matrix
