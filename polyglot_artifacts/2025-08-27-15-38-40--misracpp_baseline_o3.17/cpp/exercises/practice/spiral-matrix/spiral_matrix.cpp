#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<unsigned int>> spiral_matrix(std::size_t size) {
    // Return an empty matrix for size 0 – avoids allocating unnecessary memory.
    if (size == 0) {
        return {};
    }

    // Pre-allocate the square matrix filled with zeros.
    std::vector<std::vector<unsigned int>> matrix(size, std::vector<unsigned int>(size, 0));

    std::size_t top    = 0;
    std::size_t bottom = size - 1;
    std::size_t left   = 0;
    std::size_t right  = size - 1;

    unsigned int value   = 1;

    while (top <= bottom && left <= right) {
        /* 1. Move → along the current top row. */
        for (std::size_t col = left; col <= right; ++col) {
            matrix[top][col] = value++;
        }
        ++top;

        /* 2. Move ↓ along the current right column. */
        for (std::size_t row = top; row <= bottom; ++row) {
            matrix[row][right] = value++;
        }
        // Guard against size_t under-flow before decrementing.
        if (right == 0) break;
        --right;

        /* 3. Move ← along the current bottom row, if any rows remain. */
        if (top <= bottom) {
            for (std::size_t col = right + 1; col-- > left;) {
                matrix[bottom][col] = value++;
            }
            // Guard against size_t under-flow before decrementing.
            if (bottom == 0) break;
            --bottom;
        }

        /* 4. Move ↑ along the current left column, if any columns remain. */
        if (left <= right) {
            for (std::size_t row = bottom + 1; row-- > top;) {
                matrix[row][left] = value++;
            }
            ++left;
        }
    }

    // All cells are now filled in spiral order.
    return matrix;
}

}  // namespace spiral_matrix
