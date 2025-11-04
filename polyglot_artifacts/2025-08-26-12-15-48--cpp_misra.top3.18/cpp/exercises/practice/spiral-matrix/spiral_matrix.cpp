#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral_matrix(matrix_size_t size)
{
    matrix_t matrix(size, std::vector<matrix_value_t>(size, static_cast<matrix_value_t>(0U)));

    matrix_value_t value = static_cast<matrix_value_t>(1U);
    matrix_size_t layer = static_cast<matrix_size_t>(0U);

    while ((layer * static_cast<matrix_size_t>(2U)) < size)
    {
        matrix_size_t first = layer;
        matrix_size_t last = (size - layer) - static_cast<matrix_size_t>(1U);

        // Top row (left to right)
        for (matrix_size_t i = first; i <= last; ++i)
        {
            matrix[first][i] = value;
            value = value + static_cast<matrix_value_t>(1U);
        }

        // Right column (top to bottom)
        for (matrix_size_t i = first + static_cast<matrix_size_t>(1U); i <= last; ++i)
        {
            matrix[i][last] = value;
            value = value + static_cast<matrix_value_t>(1U);
        }

        // Bottom row (right to left)
        if (last > first)
        {
            for (matrix_size_t i = last - static_cast<matrix_size_t>(1U); i >= first; --i)
            {
                matrix[last][i] = value;
                value = value + static_cast<matrix_value_t>(1U);
                if (i == first)
                {
                    break;
                }
            }
        }

        // Left column (bottom to top)
        if (last > first)
        {
            for (matrix_size_t i = last - static_cast<matrix_size_t>(1U); i > first; --i)
            {
                matrix[i][first] = value;
                value = value + static_cast<matrix_value_t>(1U);
            }
        }

        layer = layer + static_cast<matrix_size_t>(1U);
    }

    return matrix;
}

}  // namespace spiral_matrix
