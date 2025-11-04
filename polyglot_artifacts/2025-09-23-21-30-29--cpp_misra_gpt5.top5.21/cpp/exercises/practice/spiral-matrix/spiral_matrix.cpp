#include "spiral_matrix.h"

#include <cstddef>   // for std::size_t

namespace spiral_matrix {

std::vector<std::vector<value_type>> spiral_matrix(std::uint32_t size) {
    if ((size == static_cast<std::uint32_t>(0U))) {
        return std::vector<std::vector<value_type>>{};
    }

    const std::size_t n_sz = static_cast<std::size_t>(size);
    std::vector<std::vector<value_type>> matrix(
        n_sz, std::vector<value_type>(n_sz, static_cast<value_type>(0)));

    value_type value = static_cast<value_type>(1);
    std::uint32_t top = static_cast<std::uint32_t>(0U);
    std::uint32_t bottom = (size - static_cast<std::uint32_t>(1U));
    std::uint32_t left = static_cast<std::uint32_t>(0U);
    std::uint32_t right = (size - static_cast<std::uint32_t>(1U));

    while (((top <= bottom) && (left <= right))) {
        // Fill top row: left -> right
        for (std::uint32_t col = left; (col <= right); ++col) {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = value;
            ++value;
        }
        ++top;

        // Fill right column: top -> bottom
        for (std::uint32_t row = top; (row <= bottom); ++row) {
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = value;
            ++value;
        }
        if ((right > static_cast<std::uint32_t>(0U))) {
            --right;
        } else {
            // Prevent underflow, though loop condition should guard in normal cases.
            right = static_cast<std::uint32_t>(0U);
        }

        // Fill bottom row: right -> left (if there is a remaining row)
        if (((top <= bottom) && (left <= right))) {
            for (std::uint32_t col = right; ; --col) {
                matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = value;
                ++value;
                if ((col == left)) {
                    break;
                }
            }
            if ((bottom > static_cast<std::uint32_t>(0U))) {
                --bottom;
            } else {
                bottom = static_cast<std::uint32_t>(0U);
            }
        }

        // Fill left column: bottom -> top (if there is a remaining column)
        if (((left <= right) && (top <= bottom))) {
            for (std::uint32_t row = bottom; ; --row) {
                matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(left)] = value;
                ++value;
                if ((row == top)) {
                    break;
                }
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
