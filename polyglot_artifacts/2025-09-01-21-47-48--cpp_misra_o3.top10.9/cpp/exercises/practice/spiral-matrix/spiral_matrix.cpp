#include "spiral_matrix.h"

#include <vector>
#include <cstdint>

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>>
{
    /* Create an empty square matrix filled with zeroes. */
    auto matrix
        = std::vector<std::vector<std::uint32_t>>(size, std::vector<std::uint32_t>(size, 0U));

    if (size == 0U) {
        /* Nothing to do, return the empty matrix. */
        return matrix;
    }

    std::uint32_t current { 1U };
    std::uint32_t left    { 0U };
    std::uint32_t right   { size - 1U };
    std::uint32_t top     { 0U };
    std::uint32_t bottom  { size - 1U };

    while ((left <= right) && (top <= bottom)) {
        /* Traverse from left to right along the current top row. */
        for (std::uint32_t col { left }; col <= right; ++col) {
            matrix[top][col] = current;
            ++current;
        }
        ++top;

        /* Traverse from top to bottom along the current right column. */
        for (std::uint32_t row { top }; row <= bottom; ++row) {
            matrix[row][right] = current;
            ++current;
        }
        /* Guard against underflow when size == 1. */
        if (right == 0U) {
            break;
        }
        --right;

        /* Traverse from right to left along the current bottom row, if any rows remain. */
        if (top <= bottom) {
            for (std::uint32_t col { right + 1U }; col-- > left; ) {
                matrix[bottom][col] = current;
                ++current;
            }
            /* Guard against underflow when size == 1. */
            if (bottom == 0U) {
                break;
            }
            --bottom;
        }

        /* Traverse from bottom to top along the current left column, if any columns remain. */
        if (left <= right) {
            for (std::uint32_t row { bottom + 1U }; row-- > top; ) {
                matrix[row][left] = current;
                ++current;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
