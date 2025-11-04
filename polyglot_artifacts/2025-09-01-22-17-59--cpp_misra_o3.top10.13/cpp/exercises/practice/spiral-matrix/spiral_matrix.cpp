#include "spiral_matrix.h"

namespace spiral_matrix {


[[nodiscard]] auto spiral(std::uint32_t size) -> Matrix
{
    if (size == static_cast<std::uint32_t>(0U)) {
        return {};
    }

    Matrix matrix(
        size,
        std::vector<std::uint32_t>(size, static_cast<std::uint32_t>(0U)));

    std::uint32_t top    = static_cast<std::uint32_t>(0U);
    std::uint32_t bottom = static_cast<std::uint32_t>(size - static_cast<std::uint32_t>(1U));
    std::uint32_t left   = static_cast<std::uint32_t>(0U);
    std::uint32_t right  = static_cast<std::uint32_t>(size - static_cast<std::uint32_t>(1U));

    std::uint32_t current = static_cast<std::uint32_t>(1U);

    while ((top <= bottom) && (left <= right)) {
        /* Traverse from left to right across the top row */
        for (std::uint32_t col = left; col <= right; ++col) {
            matrix[top][col] = current;
            ++current;
        }
        ++top;
        if (top > bottom) {
            break;
        }

        /* Traverse from top to bottom along the right column */
        for (std::uint32_t row = top; row <= bottom; ++row) {
            matrix[row][right] = current;
            ++current;
        }
        if (right == static_cast<std::uint32_t>(0U)) {
            break;
        }
        --right;
        if (left > right) {
            break;
        }

        /* Traverse from right to left across the bottom row */
        for (std::uint32_t col = right; ; --col) {
            matrix[bottom][col] = current;
            ++current;
            if (col == left) {
                break;
            }
        }
        if (bottom == static_cast<std::uint32_t>(0U)) {
            break;
        }
        --bottom;
        if (top > bottom) {
            break;
        }

        /* Traverse from bottom to top along the left column */
        for (std::uint32_t row = bottom; ; --row) {
            matrix[row][left] = current;
            ++current;
            if (row == top) {
                break;
            }
        }
        ++left;
    }

    return matrix;
}

/* Wrapper required by the test-suite */
[[nodiscard]] auto spiral_matrix(std::uint32_t size) -> Matrix
{
    return spiral(size);
}

}  // namespace spiral_matrix
