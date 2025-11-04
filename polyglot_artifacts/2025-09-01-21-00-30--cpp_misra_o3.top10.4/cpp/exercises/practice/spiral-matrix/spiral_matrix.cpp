#include "spiral_matrix.h"
#include <vector>
#include <cstdint>

namespace spiral_matrix {


auto spiral_matrix(std::uint32_t size) -> matrix_t
{
    /* create size×size matrix initialised with zeros */
    matrix_t matrix(size, std::vector<std::uint32_t>(size, 0U));

    if(size == 0U) {
        return matrix;
    }

    std::uint32_t top    = 0U;
    std::uint32_t bottom = size - 1U;
    std::uint32_t left   = 0U;
    std::uint32_t right  = size - 1U;

    std::uint32_t value  = 1U;

    while((top <= bottom) && (left <= right)) {

        /* top row (left → right) */
        for(std::uint32_t col = left; col <= right; ++col) {
            matrix[top][col] = value;
            ++value;
        }
        ++top;

        /* right column (top → bottom) */
        for(std::uint32_t row = top; row <= bottom; ++row) {
            matrix[row][right] = value;
            ++value;
        }

        if(right == 0U) { /* prevent unsigned under-flow before decrement */
            break;
        }
        --right;

        /* bottom row (right → left) */
        if(top <= bottom) {
            for(std::int32_t col_s = static_cast<std::int32_t>(right);
                col_s >= static_cast<std::int32_t>(left);
                --col_s) {
                matrix[bottom][static_cast<std::uint32_t>(col_s)] = value;
                ++value;
            }
            if(bottom == 0U) {
                /* cannot decrement further without under-flow */
                break;
            }
            --bottom;
        }

        /* left column (bottom → top) */
        if(left <= right) {
            for(std::int32_t row_s = static_cast<std::int32_t>(bottom);
                row_s >= static_cast<std::int32_t>(top);
                --row_s) {
                matrix[static_cast<std::uint32_t>(row_s)][left] = value;
                ++value;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
