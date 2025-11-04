#include "spiral_matrix.h"
#include <vector>
#include <cstdint>

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>> {
    if (size == 0U) {
        return {};
    }

    std::vector<std::vector<std::uint32_t>> matrix(
        static_cast<std::size_t>(size),
        std::vector<std::uint32_t>(static_cast<std::size_t>(size), 0U));

    std::uint32_t top = 0U;
    std::uint32_t bottom = size - 1U;
    std::uint32_t left = 0U;
    std::uint32_t right = size - 1U;

    std::uint32_t value = 1U;
    const std::uint32_t max_value = (size * size);

    while (value <= max_value) {
        /* Fill top row */
        for (std::uint32_t col = left; col <= right; ++col) {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = value;
            ++value;
        }
        ++top;

        /* Fill right column */
        if ((value > max_value)) { break; }
        for (std::uint32_t row = top; row <= bottom; ++row) {
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = value;
            ++value;
        }
        if (right == 0U) {
            break;
        }
        --right;

        /* Fill bottom row */
        if ((value > max_value)) { break; }
        for (std::uint32_t col_offset = 0U; col_offset <= (right - left); ++col_offset) {
            const std::uint32_t col = right - col_offset;
            matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = value;
            ++value;
        }
        if (bottom == 0U) {
            break;
        }
        --bottom;

        /* Fill left column */
        if ((value > max_value)) { break; }
        for (std::uint32_t row_offset = 0U; row_offset <= (bottom - top); ++row_offset) {
            const std::uint32_t row = bottom - row_offset;
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(left)] = value;
            ++value;
        }
        ++left;
    }

    return matrix;
}

}  // namespace spiral_matrix
