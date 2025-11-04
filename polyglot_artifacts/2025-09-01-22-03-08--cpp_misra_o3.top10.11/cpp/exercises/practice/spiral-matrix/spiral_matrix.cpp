#include "spiral_matrix.h"
#include <cstdint>
#include <vector>
#include <cstddef>

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> Matrix
{
    Matrix matrix {};

    if(size == 0U)
    {
        return matrix;
    }

    /* Create an empty square matrix of the requested size */
    matrix.assign(static_cast<std::size_t>(size),
                  std::vector<std::uint32_t>(static_cast<std::size_t>(size), 0U));

    std::uint32_t value = 1U;

    /* Signed counters avoid unsigned wrap-around while iterating backwards */
    std::int32_t top    = 0;
    std::int32_t left   = 0;
    std::int32_t bottom = static_cast<std::int32_t>(size) - 1;
    std::int32_t right  = static_cast<std::int32_t>(size) - 1;

    while((top <= bottom) && (left <= right))
    {
        /* traverse from left → right on the current top row */
        for(std::int32_t col = left; col <= right; ++col)
        {
            matrix[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = value;
            ++value;
        }
        ++top;

        /* traverse from top → bottom on the current right column */
        for(std::int32_t row = top; row <= bottom; ++row)
        {
            matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = value;
            ++value;
        }
        --right;

        /* traverse from right → left on the current bottom row, if any rows remain */
        if(top <= bottom)
        {
            for(std::int32_t col = right; col >= left; --col)
            {
                matrix[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = value;
                ++value;
            }
            --bottom;
        }

        /* traverse from bottom → top on the current left column, if any columns remain */
        if(left <= right)
        {
            for(std::int32_t row = bottom; row >= top; --row)
            {
                matrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(left)] = value;
                ++value;
            }
            ++left;
        }
    }

    return matrix;
}

}  // namespace spiral_matrix
