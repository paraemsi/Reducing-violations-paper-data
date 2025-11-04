#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    if (size == 0) {
        return {};
    }

    std::vector<std::vector<unsigned int>> matrix(size,
                                                 std::vector<unsigned int>(size, 0));

    int left = 0;
    int right = static_cast<int>(size) - 1;
    int top = 0;
    int bottom = static_cast<int>(size) - 1;
    unsigned int value = 1;

    while (left <= right && top <= bottom) {
        // Fill top row (left → right)
        for (int col = left; col <= right; ++col) {
            matrix[top][col] = value++;
        }
        ++top;

        // Fill right column (top → bottom)
        for (int row = top; row <= bottom; ++row) {
            matrix[row][right] = value++;
        }
        --right;

        // Fill bottom row (right → left)
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                matrix[bottom][col] = value++;
            }
            --bottom;
        }

        // Fill left column (bottom → top)
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
