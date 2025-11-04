#include "spiral_matrix.h"

#include <vector>

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    std::vector<std::vector<unsigned int>> matrix(size, std::vector<unsigned int>(size, 0));
    unsigned int value = 1;
    std::size_t top = 0, bottom = size ? size - 1 : 0;
    std::size_t left = 0, right = size ? size - 1 : 0;

    while (top <= bottom && left <= right && size > 0) {
        // Fill top row
        for (std::size_t col = left; col <= right; ++col) {
            matrix[top][col] = value++;
        }
        ++top;

        // Fill right column
        for (std::size_t row = top; row <= bottom; ++row) {
            matrix[row][right] = value++;
        }
        if (right == 0) break;
        --right;

        // Fill bottom row
        if (top <= bottom) {
            for (std::size_t col = right + 1; col-- > left;) {
                matrix[bottom][col] = value++;
            }
            if (bottom == 0) break;
            --bottom;
        }

        // Fill left column
        if (left <= right) {
            for (std::size_t row = bottom + 1; row-- > top;) {
                matrix[row][left] = value++;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
