#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral(std::size_t size) {
    if (size == 0U) {
        return matrix_t{};
    }

    matrix_t matrix(size, std::vector<std::uint32_t>(size, 0U));

    std::size_t top = 0U;
    std::size_t bottom = size - 1U;
    std::size_t left = 0U;
    std::size_t right = size - 1U;

    std::uint32_t value = 1U;

    while ((left <= right) && (top <= bottom)) {
        for (std::size_t col = left; col <= right; ++col) {
            matrix[top][col] = value;
            ++value;
        }
        top = top + 1U;

        for (std::size_t row = top; row <= bottom; ++row) {
            matrix[row][right] = value;
            ++value;
        }
        if (right > 0U) {
            right = right - 1U;
        } else {
            // Prevent underflow; loop condition will terminate further iterations.
            right = 0U;
        }

        if (top <= bottom) {
            std::size_t col = right;
            while (true) {
                if (col < left) {
                    break;
                }
                matrix[bottom][col] = value;
                ++value;
                if (col == left) {
                    break;
                }
                col = col - 1U;
            }
            if (bottom > 0U) {
                bottom = bottom - 1U;
            } else {
                bottom = 0U;
            }
        } else {
            // No bottom row to fill in this layer.
        }

        if (left <= right) {
            std::size_t row = bottom;
            while (true) {
                if (row < top) {
                    break;
                }
                matrix[row][left] = value;
                ++value;
                if (row == top) {
                    break;
                }
                row = row - 1U;
            }
            left = left + 1U;
        } else {
            // No left column to fill in this layer.
        }
    }

    return matrix;
}

matrix_t spiral_matrix(std::size_t size) {
    return spiral(size);
}

}  // namespace spiral_matrix
