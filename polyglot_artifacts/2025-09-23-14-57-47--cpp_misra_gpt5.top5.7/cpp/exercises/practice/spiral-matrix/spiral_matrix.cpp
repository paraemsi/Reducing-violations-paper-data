#include "spiral_matrix.h"

namespace spiral_matrix {

matrix_t spiral_matrix(std::size_t size) {
    matrix_t result(size, std::vector<std::uint32_t>(size, static_cast<std::uint32_t>(0U)));

    if (size == static_cast<std::size_t>(0U)) {
        return result;
    } else {
        // boundaries
        std::size_t top = static_cast<std::size_t>(0U);
        std::size_t left = static_cast<std::size_t>(0U);
        std::size_t bottom = size - static_cast<std::size_t>(1U);
        std::size_t right = size - static_cast<std::size_t>(1U);

        std::uint32_t value = static_cast<std::uint32_t>(1U);

        while ((left <= right) && (top <= bottom)) {
            // top row: left -> right
            for (std::size_t col = left; col <= right; ++col) {
                result.at(top).at(col) = value;
                ++value;
            }
            ++top;

            // right column: top -> bottom
            for (std::size_t row = top; row <= bottom; ++row) {
                result.at(row).at(right) = value;
                ++value;
            }
            if (right == static_cast<std::size_t>(0U)) {
                // Prevent underflow if size == 0 (already handled) or bounds cross
                // This guard is defensive; loop condition should prevent invalid state.
            }
            if (right > static_cast<std::size_t>(0U)) {
                --right;
            } else {
                // If right is 0, decrement would underflow; break if bounds crossed.
                // This path should not normally execute due to while-condition.
            }

            // bottom row: right -> left (only if still within bounds)
            if ((top <= bottom) && (left <= right)) {
                for (std::size_t col = right + static_cast<std::size_t>(1U); col-- > left; ) {
                    result.at(bottom).at(col) = value;
                    ++value;
                }
                if (bottom > static_cast<std::size_t>(0U)) {
                    --bottom;
                } else {
                    // Prevent underflow as above.
                }
            }

            // left column: bottom -> top (only if still within bounds)
            if ((left <= right) && (top <= bottom)) {
                for (std::size_t row = bottom + static_cast<std::size_t>(1U); row-- > top; ) {
                    result.at(row).at(left) = value;
                    ++value;
                }
                ++left;
            }
        }

        return result;
    }
}

}  // namespace spiral_matrix
