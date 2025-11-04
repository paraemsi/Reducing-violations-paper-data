#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::size_t size) -> matrix
{
    if (size == static_cast<std::size_t>(0U)) {
        return matrix{};
    }

    matrix result(size, std::vector<value_type>(size, static_cast<value_type>(0)));

    std::size_t top = static_cast<std::size_t>(0U);
    std::size_t bottom = static_cast<std::size_t>(size - static_cast<std::size_t>(1U));
    std::size_t left = static_cast<std::size_t>(0U);
    std::size_t right = static_cast<std::size_t>(size - static_cast<std::size_t>(1U));

    value_type cur = static_cast<value_type>(1);

    while ((top <= bottom) && (left <= right)) {
        // Top row: left -> right
        for (std::size_t col = left; col <= right; ++col) {
            result[top][col] = cur;
            ++cur;
        }
        ++top;
        if (top > bottom) {
            break;
        }

        // Right column: top -> bottom
        for (std::size_t row = top; row <= bottom; ++row) {
            result[row][right] = cur;
            ++cur;
        }
        if (left == right) {
            break;
        }
        --right;

        // Bottom row: right -> left
        {
            const std::size_t span = right - left;  // safe: left <= right here
            for (std::size_t offset = static_cast<std::size_t>(0U); offset <= span; ++offset) {
                const std::size_t col = right - offset;
                result[bottom][col] = cur;
                ++cur;
            }
        }
        if (bottom == static_cast<std::size_t>(0U)) {
            // Defensive: avoid underflow on the next decrement, though logically we should not hit this with valid bounds
        }
        --bottom;

        // Left column: bottom -> top (only if bounds still valid)
        if ((top <= bottom) && (left <= right)) {
            const std::size_t span = bottom - top;  // safe: top <= bottom here
            for (std::size_t offset = static_cast<std::size_t>(0U); offset <= span; ++offset) {
                const std::size_t row = bottom - offset;
                result[row][left] = cur;
                ++cur;
            }
        }
        ++left;
    }

    return result;
}

}  // namespace spiral_matrix
