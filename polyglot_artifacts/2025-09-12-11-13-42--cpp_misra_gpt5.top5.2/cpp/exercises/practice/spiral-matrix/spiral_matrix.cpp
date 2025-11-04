#include "spiral_matrix.h"

#include <limits>

namespace spiral_matrix {

matrix_t spiral(std::size_t size)
{
    if (size == 0U) {
        return matrix_t{};
    }

    const std::uint64_t size64 = static_cast<std::uint64_t>(size);
    const std::uint64_t max32 = static_cast<std::uint64_t>(std::numeric_limits<std::uint32_t>::max());
    // Prevent overflow in size64 * size64 and ensure the spiral values fit in std::uint32_t
    if ((size64 != 0ULL) && (size64 > (max32 / size64))) {
        // The sequence 1..(size*size) would not fit into std::uint32_t values.
        return matrix_t{};
    }
    const std::uint64_t max_n_64 = (size64 * size64);

    const std::size_t N = size;

    matrix_t m(N, std::vector<std::uint32_t>(N, 0U));

    std::size_t left = 0U;
    std::size_t right = (N - 1U);
    std::size_t top = 0U;
    std::size_t bottom = (N - 1U);

    std::uint32_t val = 1U;
    const std::uint32_t val_max = static_cast<std::uint32_t>(max_n_64);

    while ((left <= right) && (top <= bottom)) {
        // top row: left -> right
        for (std::size_t col = left; col <= right; ++col) {
            m[top][col] = val;
            ++val;
        }
        ++top;
        if (top > bottom) {
            break;
        }

        // right column: top -> bottom
        for (std::size_t row = top; row <= bottom; ++row) {
            m[row][right] = val;
            ++val;
        }
        if (right == 0U) {
            // Should not happen for N > 0, guard against underflow.
            break;
        }
        --right;
        if (left > right) {
            break;
        }

        // bottom row: right -> left
        {
            std::size_t col = right;
            for (;;) {
                m[bottom][col] = val;
                ++val;
                if (col == left) {
                    break;
                }
                --col;
            }
        }
        if (bottom == 0U) {
            // Should not happen for N > 0, guard against underflow.
            break;
        }
        --bottom;
        if (top > bottom) {
            break;
        }

        // left column: bottom -> top
        {
            std::size_t row = bottom;
            for (;;) {
                m[row][left] = val;
                ++val;
                if (row == top) {
                    break;
                }
                --row;
            }
        }
        ++left;
        if (left > right) {
            break;
        }

        // Defensive: stop if we've filled all values
        if (val > val_max) {
            break;
        }
    }

    return m;
}

matrix_t spiral_matrix(std::size_t size)
{
    return spiral(size);
}

}  // namespace spiral_matrix
