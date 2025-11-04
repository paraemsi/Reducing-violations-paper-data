#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::size_t size) noexcept -> matrix {
    if (size == 0U) {
        return matrix{};
    }

    using cell_t = typename matrix::value_type::value_type;
    matrix result(
        size, std::vector<cell_t>(size, static_cast<cell_t>(0)));

    std::size_t top = 0U;
    std::size_t bottom = size - 1U;
    std::size_t left = 0U;
    std::size_t right = size - 1U;

    cell_t value = static_cast<cell_t>(1);

    while ((left <= right) && (top <= bottom)) {
        // Left to right across the top row
        for (std::size_t i = left; (i <= right); ++i) {
            result[top][i] = value;
            ++value;
        }
        ++top;

        // Top to bottom down the right column
        for (std::size_t i = top; (i <= bottom); ++i) {
            result[i][right] = value;
            ++value;
        }
        if (right > 0U) {
            --right;
        } else {
            right = 0U;
        }

        // Right to left across the bottom row (if still within bounds)
        if ((top <= bottom) && (left <= right)) {
            for (std::size_t i = right; /* descending */ true; ) {
                result[bottom][i] = value;
                ++value;
                if (i == left) {
                    break;
                }
                --i;
            }
            if (bottom > 0U) {
                --bottom;
            } else {
                bottom = 0U;
            }
        }

        // Bottom to top up the left column (if still within bounds)
        if ((left <= right) && (top <= bottom)) {
            for (std::size_t i = bottom; /* descending */ true; ) {
                result[i][left] = value;
                ++value;
                if (i == top) {
                    break;
                }
                --i;
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
