#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(unsigned int size) {
    if (size == 0) {
        return {};
    }

    std::vector<std::vector<unsigned int>> matrix(size, std::vector<unsigned int>(size, 0));

    int n = static_cast<int>(size);

    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;

    unsigned int value = 1;

    while (left <= right && top <= bottom) {
        for (int c = left; c <= right; ++c) {
            matrix[top][c] = value++;
        }
        ++top;

        for (int r = top; r <= bottom; ++r) {
            matrix[r][right] = value++;
        }
        --right;

        if (top <= bottom) {
            for (int c = right; c >= left; --c) {
                matrix[bottom][c] = value++;
            }
            --bottom;
        }

        if (left <= right) {
            for (int r = bottom; r >= top; --r) {
                matrix[r][left] = value++;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
