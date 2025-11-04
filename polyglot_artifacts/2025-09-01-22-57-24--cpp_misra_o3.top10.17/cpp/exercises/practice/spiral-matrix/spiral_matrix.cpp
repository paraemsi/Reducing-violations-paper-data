#include "spiral_matrix.h"

#include <cstdint>

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> matrix
{
    /* size == 0 → empty result */
    if (size == static_cast<std::uint32_t>(0)) {
        return matrix{};
    }

    matrix result(size, std::vector<std::uint32_t>(size, static_cast<std::uint32_t>(0)));

    std::uint32_t top    = static_cast<std::uint32_t>(0);
    std::uint32_t left   = static_cast<std::uint32_t>(0);
    std::uint32_t bottom = static_cast<std::uint32_t>(size - static_cast<std::uint32_t>(1));
    std::uint32_t right  = bottom;

    std::uint32_t value = static_cast<std::uint32_t>(1);

    while ((top <= bottom) && (left <= right)) {
        /* left-to-right across the top row */
        for (std::uint32_t col = left; col <= right; ++col) {
            result[top][col] = value;
            ++value;
        }
        ++top;

        /* top-to-bottom down the right column */
        for (std::uint32_t row = top; row <= bottom; ++row) {
            result[row][right] = value;
            ++value;
        }
        if (right == static_cast<std::uint32_t>(0)) {
            break; /* avoid underflow */
        }
        --right;

        /* right-to-left across the bottom row */
        if (top <= bottom) {
            for (std::uint32_t col = right + static_cast<std::uint32_t>(1); col > left; --col) {
                result[bottom][col - static_cast<std::uint32_t>(1)] = value;
                ++value;
            }
            if (bottom == static_cast<std::uint32_t>(0)) {
                break; /* avoid underflow */
            }
            --bottom;
        }

        /* bottom-to-top up the left column */
        if (left <= right) {
            for (std::uint32_t row = bottom + static_cast<std::uint32_t>(1); row > top; --row) {
                result[row - static_cast<std::uint32_t>(1)][left] = value;
                ++value;
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
