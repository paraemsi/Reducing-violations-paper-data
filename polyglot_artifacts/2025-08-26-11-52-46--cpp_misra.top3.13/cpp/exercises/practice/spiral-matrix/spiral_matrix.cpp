#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral_matrix(matrix_size_t size)
{
    matrix_t matrix(size, std::vector<matrix_value_t>(size, static_cast<matrix_value_t>(0U)));

    matrix_value_t value = static_cast<matrix_value_t>(1U);
    matrix_size_t layer = static_cast<matrix_size_t>(0U);

    while ((layer < (size + static_cast<matrix_size_t>(1U)) / static_cast<matrix_size_t>(2U)))
    {
        // Top row (left to right)
        for (matrix_size_t col = layer; (col < (size - layer)); ++col)
        {
            matrix[layer][col] = value;
            value = value + static_cast<matrix_value_t>(1U);
        }

        // Right column (top to bottom)
        for (matrix_size_t row = (layer + static_cast<matrix_size_t>(1U)); (row < (size - layer)); ++row)
        {
            matrix[row][size - layer - static_cast<matrix_size_t>(1U)] = value;
            value = value + static_cast<matrix_value_t>(1U);
        }

        // Bottom row (right to left)
        if ((size - layer - static_cast<matrix_size_t>(1U)) > layer)
        {
            for (matrix_size_t col = (size - layer - static_cast<matrix_size_t>(2U)); (col + static_cast<matrix_size_t>(1U)) > layer; --col)
            {
                matrix[size - layer - static_cast<matrix_size_t>(1U)][col] = value;
                value = value + static_cast<matrix_value_t>(1U);
            }
        }

        // Left column (bottom to top)
        if ((size - layer - static_cast<matrix_size_t>(1U)) > layer)
        {
            for (matrix_size_t row = (size - layer - static_cast<matrix_size_t>(2U)); (row > layer); --row)
            {
                matrix[row][layer] = value;
                value = value + static_cast<matrix_value_t>(1U);
            }
        }

        layer = layer + static_cast<matrix_size_t>(1U);
    }

    return matrix;
}

}  // namespace spiral_matrix
