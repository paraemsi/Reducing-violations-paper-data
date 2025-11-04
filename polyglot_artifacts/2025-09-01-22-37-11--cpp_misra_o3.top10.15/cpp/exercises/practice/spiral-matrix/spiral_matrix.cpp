#include "spiral_matrix.h"

#include <cstdint>
#include <vector>

namespace spiral_matrix {

auto spiral(index_t dimension) -> std::vector<std::vector<index_t>>
{
    /* Return empty matrix for zero dimension */
    if (dimension == static_cast<index_t>(0U)) {
        return {};
    }

    /* Pre-allocate the resulting 2-D container */
    std::vector<std::vector<index_t>> matrix(
        dimension,
        std::vector<index_t>(dimension, static_cast<index_t>(0U)));

    /* Boundary indices of the current ring */
    index_t top    = static_cast<index_t>(0U);
    index_t left   = static_cast<index_t>(0U);
    index_t bottom = dimension - static_cast<index_t>(1U);
    index_t right  = dimension - static_cast<index_t>(1U);

    index_t value  = static_cast<index_t>(1U);

    /* Fill the matrix one concentric ring at a time */
    while ((top <= bottom) && (left <= right)) {
        /* Traverse from left to right along the current top row */
        for (index_t col = left; col <= right; ++col) {
            matrix[top][col] = value;
            ++value;
        }
        ++top;
        if (top > bottom) {
            break;
        }

        /* Traverse from top to bottom along the current right column */
        for (index_t row = top; row <= bottom; ++row) {
            matrix[row][right] = value;
            ++value;
        }
        if (left == right) {
            break;
        }
        --right;
        if (left > right) {
            break;
        }

        /* Traverse from right to left along the current bottom row */
        for (index_t col = right; col > left; --col) {
            matrix[bottom][col] = value;
            ++value;
        }
        /* Fill the remaining left-most cell of the current bottom row */
        matrix[bottom][left] = value;
        ++value;
        --bottom;
        if (top > bottom) {
            break;
        }

        /* Traverse from bottom to top along the current left column */
        for (index_t row = bottom; row > top; --row) {
            matrix[row][left] = value;
            ++value;
        }
        ++left;
    }

    return matrix;
}

/* Public entry point expected by the unit tests.  Accepts a (signed) int,
 * verifies non-negativity, converts to the unsigned index_t, and forwards
 * to spiral().
 */
auto spiral_matrix(int dimension) -> std::vector<std::vector<index_t>>
{
    /* Negative sizes are nonsensical – return empty matrix */
    if (dimension <= 0) {
        return {};
    }

    /* Deliberate signed-to-unsigned cast – justified: range checked above */
    return spiral(static_cast<index_t>(dimension));
}

}  // namespace spiral_matrix
