#include "spiral_matrix.h"
#include <cstddef>

namespace spiral_matrix {

auto spiral_matrix(value_t size) -> matrix_t
{
    matrix_t mat{};
    if (size == static_cast<value_t>(0U)) {
        return mat;
    }

    const std::size_t n = static_cast<std::size_t>(size);
    mat.assign(n, std::vector<value_t>(n, static_cast<value_t>(0U)));

    value_t top = static_cast<value_t>(0U);
    value_t left = static_cast<value_t>(0U);
    value_t right = static_cast<value_t>(size - static_cast<value_t>(1U));
    value_t bottom = static_cast<value_t>(size - static_cast<value_t>(1U));
    value_t val = static_cast<value_t>(1U);

    while ((left <= right) && (top <= bottom)) {
        // Traverse from left to right along the top row
        for (value_t col = left; col <= right; ++col) {
            mat[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = val;
            ++val;
        }
        ++top;

        // Traverse from top to bottom along the right column
        if ((top <= bottom) && (left <= right)) {
            for (value_t row = top; row <= bottom; ++row) {
                mat[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = val;
                ++val;
            }
        }
        if (right > static_cast<value_t>(0U)) {
            --right;
        } else {
            // Prevent underflow; loop condition will terminate on next check
            right = static_cast<value_t>(0U);
        }

        // Traverse from right to left along the bottom row
        if ((top <= bottom) && (left <= right)) {
            value_t col = right;
            for (;;) {
                mat[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = val;
                ++val;
                if (col == left) {
                    break;
                }
                --col;
            }
        }
        if (bottom > static_cast<value_t>(0U)) {
            --bottom;
        } else {
            bottom = static_cast<value_t>(0U);
        }

        // Traverse from bottom to top along the left column
        if ((top <= bottom) && (left <= right)) {
            value_t row = bottom;
            for (;;) {
                mat[static_cast<std::size_t>(row)][static_cast<std::size_t>(left)] = val;
                ++val;
                if (row == top) {
                    break;
                }
                --row;
            }
        }
        ++left;
    }

    return mat;
}

}  // namespace spiral_matrix
