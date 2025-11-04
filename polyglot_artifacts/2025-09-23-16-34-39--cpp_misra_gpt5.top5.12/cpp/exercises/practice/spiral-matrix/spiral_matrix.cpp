#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral_matrix(std::size_t size)
{
    if (size == 0U) {
        return matrix_t{};
    }

    matrix_t matrix(size, std::vector<value_type>(size, value_type{0U}));

    std::size_t left = 0U;
    std::size_t right = size - 1U;
    std::size_t top = 0U;
    std::size_t bottom = size - 1U;

    value_type val = static_cast<value_type>(1U);

    while ((left <= right) && (top <= bottom)) {
        // Fill top row from left to right.
        for (std::size_t col = left; col <= right; ++col) {
            matrix[top][col] = val;
            ++val;
        }
        ++top;

        // Fill right column from top to bottom.
        if ((top <= bottom) && (left <= right)) {
            for (std::size_t row = top; row <= bottom; ++row) {
                matrix[row][right] = val;
                ++val;
            }
            if (right > 0U) {
                --right;
            } else {
                right = 0U;
            }
        }

        // Fill bottom row from right to left.
        if ((left <= right) && (top <= bottom)) {
            std::size_t col_iter = right;
            for (;;) {
                matrix[bottom][col_iter] = val;
                ++val;
                if (col_iter == left) {
                    break;
                }
                --col_iter;
            }

            if (bottom > 0U) {
                --bottom;
            } else {
                bottom = 0U;
            }
        }

        // Fill left column from bottom to top.
        if ((top <= bottom) && (left <= right)) {
            std::size_t row_iter = bottom;
            for (;;) {
                matrix[row_iter][left] = val;
                ++val;
                if (row_iter == top) {
                    break;
                }
                --row_iter;
            }
            ++left;
        }
    }

    return matrix;
}

matrix_t generate(std::size_t size)
{
    return spiral_matrix(size);
}

}  // namespace spiral_matrix
