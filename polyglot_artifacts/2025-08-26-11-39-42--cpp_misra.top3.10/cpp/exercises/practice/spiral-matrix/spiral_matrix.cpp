#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral_matrix(matrix_size_t size)
{
    matrix_t matrix(size, std::vector<matrix_value_t>(size, static_cast<matrix_value_t>(0U)));

    if (size == static_cast<matrix_size_t>(0U)) {
        return matrix;
    }

    matrix_value_t value = static_cast<matrix_value_t>(1U);
    matrix_size_t layer = static_cast<matrix_size_t>(0U);
    matrix_size_t n = size;

    while ((layer < (n + static_cast<matrix_size_t>(1U)) / static_cast<matrix_size_t>(2U))) {
        // Top row (left to right)
        for (matrix_size_t col = layer; (col < (n - layer)); ++col) {
            matrix[layer][col] = value;
            value = static_cast<matrix_value_t>(value + static_cast<matrix_value_t>(1U));
        }
        // Right column (top to bottom)
        for (matrix_size_t row = (layer + static_cast<matrix_size_t>(1U)); (row < (n - layer)); ++row) {
            matrix[row][n - layer - static_cast<matrix_size_t>(1U)] = value;
            value = static_cast<matrix_value_t>(value + static_cast<matrix_value_t>(1U));
        }
        // Bottom row (right to left)
        if ((n - layer - static_cast<matrix_size_t>(1U)) > layer) {
            for (matrix_size_t col = (n - layer - static_cast<matrix_size_t>(2U)); (col + static_cast<matrix_size_t>(1U)) > layer; --col) {
                matrix[n - layer - static_cast<matrix_size_t>(1U)][col] = value;
                value = static_cast<matrix_value_t>(value + static_cast<matrix_value_t>(1U));
            }
        }
        // Left column (bottom to top)
        if ((n - layer - static_cast<matrix_size_t>(1U)) > layer) {
            for (matrix_size_t row = (n - layer - static_cast<matrix_size_t>(2U)); (row > layer); --row) {
                matrix[row][layer] = value;
                value = static_cast<matrix_value_t>(value + static_cast<matrix_value_t>(1U));
            }
        }
        layer = static_cast<matrix_size_t>(layer + static_cast<matrix_size_t>(1U));
    }

    return matrix;
}

}  // namespace spiral_matrix
