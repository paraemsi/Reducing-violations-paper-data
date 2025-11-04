#include "spiral_matrix.h"

#include <vector>

namespace spiral_matrix {

auto spiral_matrix(std::size_t size) -> matrix_t
{
    /* Return an empty matrix for size 0 */
    if (size == static_cast<std::size_t>(0U)) {
        return {};
    }

    matrix_t result(
        size,
        std::vector<std::uint32_t>(size, static_cast<std::uint32_t>(0U)));

    std::size_t top {static_cast<std::size_t>(0U)};
    std::size_t bottom {size - static_cast<std::size_t>(1U)};
    std::size_t left {static_cast<std::size_t>(0U)};
    std::size_t right {size - static_cast<std::size_t>(1U)};

    std::uint32_t current {static_cast<std::uint32_t>(1U)};

    while ((top <= bottom) && (left <= right)) {
        /* Traverse from left to right along the top row */
        for (std::size_t col {left}; col <= right; ++col) {
            result[top][col] = current;
            ++current;
        }
        ++top;

        /* Traverse from top to bottom along the right column */
        for (std::size_t row {top}; (row <= bottom); ++row) {
            result[row][right] = current;
            ++current;
        }
        if (right == static_cast<std::size_t>(0U)) {
            break; /* Prevent underflow */
        }
        --right;

        /* Traverse from right to left along the bottom row */
        if (top <= bottom) {
            for (std::size_t col_rev {right + static_cast<std::size_t>(1U)};
                 col_rev-- > left;) {
                result[bottom][col_rev] = current;
                ++current;
            }
            if (bottom == static_cast<std::size_t>(0U)) {
                break;
            }
            --bottom;
        }

        /* Traverse from bottom to top along the left column */
        if (left <= right) {
            for (std::size_t row_rev {bottom + static_cast<std::size_t>(1U)};
                 row_rev-- > top;) {
                result[row_rev][left] = current;
                ++current;
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
