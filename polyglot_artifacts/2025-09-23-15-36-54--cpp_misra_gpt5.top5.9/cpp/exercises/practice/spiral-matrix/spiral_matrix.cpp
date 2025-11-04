#include "spiral_matrix.h"

namespace spiral_matrix {

[[nodiscard]] auto spiral_matrix(std::size_t size) -> matrix
{
    const std::size_t n = size;

    matrix m(n, std::vector<value_type>(n, static_cast<value_type>(0U)));

    if (n == static_cast<std::size_t>(0U)) {
        return m;
    }

    std::size_t top = static_cast<std::size_t>(0U);
    std::size_t bottom = n - static_cast<std::size_t>(1U);
    std::size_t left = static_cast<std::size_t>(0U);
    std::size_t right = n - static_cast<std::size_t>(1U);

    value_type val = static_cast<value_type>(1U);

    while ((left <= right) && (top <= bottom)) {
        // Top row: left -> right
        for (std::size_t c = left; c <= right; ++c) {
            m[top][c] = val;
            ++val;
        }
        if (top == bottom) {
            break;
        }
        ++top;

        // Right column: top -> bottom
        for (std::size_t r = top; r <= bottom; ++r) {
            m[r][right] = val;
            ++val;
        }
        if (left == right) {
            break;
        }
        --right;

        // Bottom row: right -> left
        {
            std::size_t c = right;
            while (true) {
                m[bottom][c] = val;
                ++val;
                if (c == left) {
                    break;
                }
                --c;
            }
        }
        if (top == bottom) {
            break;
        }
        --bottom;

        // Left column: bottom -> top
        if (left == right) {
            break;
        }
        {
            std::size_t r = bottom;
            while (true) {
                m[r][left] = val;
                ++val;
                if (r == top) {
                    break;
                }
                --r;
            }
        }
        ++left;
    }

    return m;
}

}  // namespace spiral_matrix
