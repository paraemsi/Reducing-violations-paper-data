#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<matrix_size_t>> spiral_matrix(matrix_size_t size)
{
    std::vector<std::vector<matrix_size_t>> matrix(size, std::vector<matrix_size_t>(size, static_cast<matrix_size_t>(0)));

    if (size == static_cast<matrix_size_t>(0)) {
        return matrix;
    }

    matrix_size_t value = static_cast<matrix_size_t>(1);
    matrix_size_t top = static_cast<matrix_size_t>(0);
    matrix_size_t bottom = size - static_cast<matrix_size_t>(1);
    matrix_size_t left = static_cast<matrix_size_t>(0);
    matrix_size_t right = size - static_cast<matrix_size_t>(1);

    while ((top <= bottom) && (left <= right)) {
        // Fill top row
        for (matrix_size_t col = left; col <= right; ++col) {
            matrix[top][col] = value;
            value = value + static_cast<matrix_size_t>(1);
        }
        top = top + static_cast<matrix_size_t>(1);

        // Fill right column
        for (matrix_size_t row = top; row <= bottom; ++row) {
            matrix[row][right] = value;
            value = value + static_cast<matrix_size_t>(1);
        }
        if (right == static_cast<matrix_size_t>(0)) {
            break;
        }
        right = right - static_cast<matrix_size_t>(1);

        // Fill bottom row
        if (top <= bottom) {
            for (matrix_size_t col = right + static_cast<matrix_size_t>(1); col-- > left;) {
                matrix[bottom][col] = value;
                value = value + static_cast<matrix_size_t>(1);
            }
            if (bottom == static_cast<matrix_size_t>(0)) {
                break;
            }
            bottom = bottom - static_cast<matrix_size_t>(1);
        }

        // Fill left column
        if (left <= right) {
            for (matrix_size_t row = bottom + static_cast<matrix_size_t>(1); row-- > top;) {
                matrix[row][left] = value;
                value = value + static_cast<matrix_size_t>(1);
            }
            left = left + static_cast<matrix_size_t>(1);
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
