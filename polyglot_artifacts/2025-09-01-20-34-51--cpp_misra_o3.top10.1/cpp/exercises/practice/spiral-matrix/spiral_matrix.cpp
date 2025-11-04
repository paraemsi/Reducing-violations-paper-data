#include "spiral_matrix.h"

#include <vector>
#include <cstdint>

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>> {
    if(size == static_cast<std::uint32_t>(0U)) {
        return {};
    }

    std::vector<std::vector<std::uint32_t>> matrix(
        static_cast<std::size_t>(size),
        std::vector<std::uint32_t>(static_cast<std::size_t>(size), static_cast<std::uint32_t>(0U)));

    std::uint32_t top    = static_cast<std::uint32_t>(0U);
    std::uint32_t bottom = static_cast<std::uint32_t>(size - static_cast<std::uint32_t>(1U));
    std::uint32_t left   = static_cast<std::uint32_t>(0U);
    std::uint32_t right  = static_cast<std::uint32_t>(size - static_cast<std::uint32_t>(1U));

    std::uint32_t value           = static_cast<std::uint32_t>(1U);
    const std::uint32_t total_val = static_cast<std::uint32_t>(size * size);

    while((left <= right) && (top <= bottom)) {
        /* left → right along the current top row */
        for(std::uint32_t col = left; col <= right; ++col) {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = value;
            ++value;
        }
        ++top;
        if(top > bottom) {
            break;
        }

        /* top → bottom along the current right column */
        for(std::uint32_t row = top; row <= bottom; ++row) {
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = value;
            ++value;
        }
        if(right == static_cast<std::uint32_t>(0U)) {
            break;
        }
        --right;
        if(left > right) {
            break;
        }

        /* right → left along the current bottom row */
        for(std::uint32_t col = right + static_cast<std::uint32_t>(1U); (col-- > left); ) {
            matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = value;
            ++value;
        }
        if(bottom == static_cast<std::uint32_t>(0U)) {
            break;
        }
        --bottom;
        if(top > bottom) {
            break;
        }

        /* bottom → top along the current left column */
        for(std::uint32_t row = bottom + static_cast<std::uint32_t>(1U); (row-- > top); ) {
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(left)] = value;
            ++value;
        }
        ++left;
    }

    (void)total_val;          /* silence potential unused-variable warnings */

    return matrix;
}

}  // namespace spiral_matrix
