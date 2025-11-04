#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<int> > spiral_matrix(std::size_t size) {
    if (size == 0) {
        return std::vector<std::vector<int> >();
    }

    std::vector<std::vector<int> > matrix(size, std::vector<int>(size, 0));

    int n = static_cast<int>(size);
    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;
    int value = 1;

    while (left <= right && top <= bottom) {
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = value++;
        }
        ++top;

        for (int row = top; row <= bottom; ++row) {
            matrix[row][right] = value++;
        }
        --right;

        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[bottom][col] = value++;
            }
            --bottom;
        }

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
