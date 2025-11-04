#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral_matrix(matrix_size_t size)
{
    matrix_t matrix(size, std::vector<matrix_value_t>(size, static_cast<matrix_value_t>(0U)));

    matrix_value_t value = static_cast<matrix_value_t>(1U);
    matrix_size_t left = static_cast<matrix_size_t>(0U);
    matrix_size_t right = (size == static_cast<matrix_size_t>(0U)) ? static_cast<matrix_size_t>(0U) : static_cast<matrix_size_t>(size - static_cast<matrix_size_t>(1U));
    matrix_size_t top = static_cast<matrix_size_t>(0U);
    matrix_size_t bottom = (size == static_cast<matrix_size_t>(0U)) ? static_cast<matrix_size_t>(0U) : static_cast<matrix_size_t>(size - static_cast<matrix_size_t>(1U));

    while ((left <= right) && (top <= bottom) && (size > static_cast<matrix_size_t>(0U)))
    {
        // Top row (left to right)
        for (matrix_size_t col = left; (col <= right); ++col)
        {
            matrix[top][col] = value;
            value = static_cast<matrix_value_t>(value + static_cast<matrix_value_t>(1U));
        }
        // Right column (top+1 to bottom)
        for (matrix_size_t row = (top + static_cast<matrix_size_t>(1U)); (row <= bottom); ++row)
        {
            matrix[row][right] = value;
            value = static_cast<matrix_value_t>(value + static_cast<matrix_value_t>(1U));
        }
        // Bottom row (right-1 to left), only if top < bottom
        if (top < bottom)
        {
            for (matrix_size_t col = (right - static_cast<matrix_size_t>(1U) + static_cast<matrix_size_t>(1U)); (col > left); --col)
            {
                matrix[bottom][col - static_cast<matrix_size_t>(1U)] = value;
                value = static_cast<matrix_value_t>(value + static_cast<matrix_value_t>(1U));
            }
        }
        // Left column (bottom-1 to top+1), only if left < right
        if (left < right)
        {
            for (matrix_size_t row = (bottom - static_cast<matrix_size_t>(1U) + static_cast<matrix_size_t>(1U)); (row > top + static_cast<matrix_size_t>(0U) + static_cast<matrix_size_t>(1U)); --row)
            {
                matrix[row - static_cast<matrix_size_t>(1U)][left] = value;
                value = static_cast<matrix_value_t>(value + static_cast<matrix_value_t>(1U));
            }
        }
        left = static_cast<matrix_size_t>(left + static_cast<matrix_size_t>(1U));
        right = static_cast<matrix_size_t>(right - static_cast<matrix_size_t>(1U));
        top = static_cast<matrix_size_t>(top + static_cast<matrix_size_t>(1U));
        bottom = static_cast<matrix_size_t>(bottom - static_cast<matrix_size_t>(1U));
    }

    return matrix;
}

}  // namespace spiral_matrix
