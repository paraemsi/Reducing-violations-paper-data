#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral_matrix(std::size_t size)
{
    if (size == static_cast<std::size_t>(0U)) {
        return matrix_t{};
    }

    matrix_t matrix(size, std::vector<element_t>(size, static_cast<element_t>(0U)));

    std::size_t top    = 0U;
    std::size_t bottom = size - static_cast<std::size_t>(1U);
    std::size_t left   = 0U;
    std::size_t right  = size - static_cast<std::size_t>(1U);

    element_t value = static_cast<element_t>(1U);

    while ((top <= bottom) && (left <= right)) {

        /* Fill the top row from the current left to right boundary */
        for (std::size_t col = left; col <= right; ++col) {
            matrix[top][col] = value;
            ++value;
        }
        ++top;

        /* Fill the rightmost column from the current top to bottom boundary */
        for (std::size_t row = top; row <= bottom; ++row) {
            matrix[row][right] = value;
            ++value;
        }
        if (right == static_cast<std::size_t>(0U)) {
            /* Prevent underflow when size == 1 */
            break;
        }
        --right;

        /* Fill the bottom row from the current right to left boundary */
        if (top <= bottom) {
            for (std::size_t col = right; ; ) {
                matrix[bottom][col] = value;
                ++value;
                if (col == left) {
                    break;
                }
                --col;
            }
            if (bottom == static_cast<std::size_t>(0U)) {
                /* Prevent underflow when size == 1 */
                break;
            }
            --bottom;
        }

        /* Fill the leftmost column from the current bottom to top boundary */
        if ((left <= right) && (top <= bottom)) {
            for (std::size_t row = bottom; ; ) {
                matrix[row][left] = value;
                ++value;
                if (row == top) {
                    break;
                }
                --row;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
