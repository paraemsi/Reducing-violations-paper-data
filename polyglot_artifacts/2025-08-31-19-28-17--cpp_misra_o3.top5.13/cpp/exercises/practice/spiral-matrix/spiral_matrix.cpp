#include "spiral_matrix.h"

namespace spiral_matrix {

auto spiral_matrix(std::uint32_t size) -> std::vector<std::vector<std::uint32_t>>
{
    if(size == 0U)
    {
        return {};
    }

    /* Pre-allocate result matrix filled with 0 */
    std::vector<std::vector<std::uint32_t>> matrix(
        size, std::vector<std::uint32_t>(size, 0U));

    /* Boundaries of the current square ring */
    std::int32_t left   = 0;
    std::int32_t top    = 0;
    std::int32_t right  = static_cast<std::int32_t>(size) - 1;
    std::int32_t bottom = right;

    std::uint32_t value = 1U;

    /* Fill the matrix ring-by-ring */
    while((left <= right) && (top <= bottom))
    {
        /* left → right on the top row (inclusive) */
        for(std::int32_t col = left; col <= right; ++col)
        {
            matrix[static_cast<std::uint32_t>(top)]
                  [static_cast<std::uint32_t>(col)] = value;
            ++value;
        }
        ++top;
        if(top > bottom)
        {
            break;
        }

        /* top → bottom on the right column (inclusive) */
        for(std::int32_t row = top; row <= bottom; ++row)
        {
            matrix[static_cast<std::uint32_t>(row)]
                  [static_cast<std::uint32_t>(right)] = value;
            ++value;
        }
        --right;
        if(left > right)
        {
            break;
        }

        /* right → left on the bottom row (inclusive) */
        for(std::int32_t col = right; col >= left; --col)
        {
            matrix[static_cast<std::uint32_t>(bottom)]
                  [static_cast<std::uint32_t>(col)] = value;
            ++value;
        }
        --bottom;
        if(top > bottom)
        {
            break;
        }

        /* bottom → top on the left column (inclusive) */
        for(std::int32_t row = bottom; row >= top; --row)
        {
            matrix[static_cast<std::uint32_t>(row)]
                  [static_cast<std::uint32_t>(left)] = value;
            ++value;
        }
        ++left;
    }

    return matrix;
}

}  // namespace spiral_matrix
