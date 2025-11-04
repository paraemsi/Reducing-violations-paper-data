#include "spiral_matrix.h"

#include <vector>
#include <cstddef>

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t dimension) -> std::vector<std::vector<std::uint32_t>> {
    /* Handle the edge-case of a zero-sized matrix */
    if (dimension == static_cast<std::uint32_t>(0U)) {
        return {};
    }

    /* Allocate a square matrix pre-initialised with zero */
    std::vector<std::vector<std::uint32_t>> matrix(
        dimension,
        std::vector<std::uint32_t>(dimension, static_cast<std::uint32_t>(0U)));

    /* Define the current “borders” of the yet-to-be-filled rectangle */
    std::uint32_t top    = static_cast<std::uint32_t>(0U);
    std::uint32_t bottom = dimension - static_cast<std::uint32_t>(1U);
    std::uint32_t left   = static_cast<std::uint32_t>(0U);
    std::uint32_t right  = dimension - static_cast<std::uint32_t>(1U);

    std::uint32_t next_value = static_cast<std::uint32_t>(1U);

    while ((top <= bottom) && (left <= right)) {
        /* Fill the current top row (left → right) */
        for (std::uint32_t column = left; column <= right; ++column) {
            matrix[top][column] = next_value;
            ++next_value;
        }
        ++top;

        /* Fill the current right column (top → bottom) */
        for (std::uint32_t row = top; row <= bottom; ++row) {
            matrix[row][right] = next_value;
            ++next_value;
        }
        if (right > static_cast<std::uint32_t>(0U)) {
            --right;
        }

        /* Fill the current bottom row (right → left) */
        if (top <= bottom) {
            for (std::uint32_t column = right; /* condition handled inside */; --column) {
                matrix[bottom][column] = next_value;
                ++next_value;
                if (column == left) {
                    break; /* Prevent unsigned wrap-around */
                }
            }
            if (bottom > static_cast<std::uint32_t>(0U)) {
                --bottom;
            }
        }

        /* Fill the current left column (bottom → top) */
        if ((left <= right) && (top <= bottom)) {
            for (std::uint32_t row = bottom; /* condition handled inside */; --row) {
                matrix[row][left] = next_value;
                ++next_value;
                if (row == top) {
                    break; /* Prevent unsigned wrap-around */
                }
            }
            ++left;
        }
    }

    return matrix;
}

auto spiral_matrix(std::size_t dimension) -> std::vector<std::vector<std::uint32_t>> {
    /* Dimension is expected to fit into 32 bits for this exercise */
    return spiral_matrix(static_cast<std::uint32_t>(dimension));
}

}  // namespace spiral_matrix
