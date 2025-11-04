#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral_matrix(matrix_size_t size)
{
    matrix_t matrix(size, std::vector<matrix_value_t>(size, static_cast<matrix_value_t>(0U)));

    if (size == static_cast<matrix_size_t>(0U)) {
        return matrix;
    }

    matrix_value_t value = static_cast<matrix_value_t>(1U);
    matrix_size_t left = static_cast<matrix_size_t>(0U);
    matrix_size_t right = size - static_cast<matrix_size_t>(1U);
    matrix_size_t top = static_cast<matrix_size_t>(0U);
    matrix_size_t bottom = size - static_cast<matrix_size_t>(1U);

    while ((left <= right) && (top <= bottom)) {
        // Top row (left to right)
        for (matrix_size_t col = left; col <= right; ++col) {
            matrix[top][col] = value;
            value = static_cast<matrix_value_t>(value + static_cast<matrix_value_t>(1U));
        }
        top = static_cast<matrix_size_t>(top + static_cast<matrix_size_t>(1U));

        // Right column (top to bottom)
        for (matrix_size_t row = top; row <= bottom; ++row) {
            matrix[row][right] = value;
            value = static_cast<matrix_value_t>(value + static_cast<matrix_value_t>(1U));
        }
        if (right == static_cast<matrix_size_t>(0U)) {
            break;
        }
        right = static_cast<matrix_size_t>(right - static_cast<matrix_size_t>(1U));

        // Bottom row (right to left)
        if (top <= bottom) {
            for (matrix_size_t col = right + static_cast<matrix_size_t>(1U); col-- > left;) {
                matrix[bottom][col] = value;
                value = static_cast<matrix_value_t>(value + static_cast<matrix_value_t>(1U));
            }
            if (bottom == static_cast<matrix_size_t>(0U)) {
                break;
            }
            bottom = static_cast<matrix_size_t>(bottom - static_cast<matrix_size_t>(1U));
        }

        // Left column (bottom to top)
        if (left <= right) {
            for (matrix_size_t row = bottom + static_cast<matrix_size_t>(1U); row-- > top;) {
                matrix[row][left] = value;
                value = static_cast<matrix_value_t>(value + static_cast<matrix_value_t>(1U));
            }
            left = static_cast<matrix_size_t>(left + static_cast<matrix_size_t>(1U));
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
