#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral_matrix(matrix_size_t size)
{
    matrix_t matrix(size, std::vector<matrix_value_t>(size, static_cast<matrix_value_t>(0U)));

    matrix_value_t value = static_cast<matrix_value_t>(1U);
    matrix_size_t layer = static_cast<matrix_size_t>(0U);

    while ((layer < (size / static_cast<matrix_size_t>(2U))) || ((size % static_cast<matrix_size_t>(2U)) != static_cast<matrix_size_t>(0U) && (layer == (size / static_cast<matrix_size_t>(2U)))))
    {
        matrix_size_t start = layer;
        matrix_size_t end = (size - layer) - static_cast<matrix_size_t>(1U);

        // Top row (left to right)
        for (matrix_size_t col = start; col <= end; ++col)
        {
            matrix[start][col] = value;
            value = value + static_cast<matrix_value_t>(1U);
        }

        // Right column (top to bottom)
        for (matrix_size_t row = start + static_cast<matrix_size_t>(1U); row <= end; ++row)
        {
            matrix[row][end] = value;
            value = value + static_cast<matrix_value_t>(1U);
        }

        // Bottom row (right to left)
        if (end > start)
        {
            for (matrix_size_t col = end - static_cast<matrix_size_t>(1U); col >= start; --col)
            {
                matrix[end][col] = value;
                value = value + static_cast<matrix_value_t>(1U);
                if (col == start)
                {
                    break;
                }
            }
        }

        // Left column (bottom to top)
        if (end > start)
        {
            for (matrix_size_t row = end - static_cast<matrix_size_t>(1U); row > start; --row)
            {
                matrix[row][start] = value;
                value = value + static_cast<matrix_value_t>(1U);
            }
        }

        layer = layer + static_cast<matrix_size_t>(1U);
    }

    return matrix;
}

}  // namespace spiral_matrix
